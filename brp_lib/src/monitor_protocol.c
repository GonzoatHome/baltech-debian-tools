#include "brp_lib/monitor_protocol.h"
#include "brp_lib/brp_protocol.h"
#include "brp_lib/platform.h"
#include "brp_lib/frames.h"
#include "brp_lib/names.h"
#include "brp_lib/mempool.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#if defined(MOCK_TIME)
	time_t mockedtime(time_t *);
	#define time mockedtime
#endif

// ensure crossplatform compatibility
#if defined(WIN32)
	#if _MSC_VER >= 1900
		#define timezone _timezone
		#define tzset _tzset
	#elif defined(__MINGW32__)
		// MinGW with UCRT deprecates 'timezone', use '_timezone' instead
		#define timezone _timezone
		#define tzset _tzset
	#endif
	#define localtime_r(timer, buf) localtime_s(buf, timer)
#endif

typedef long long abs_time;

typedef enum {
	MONITOR_LOGS_AUTO,      // Current behavior - log when possible
	MONITOR_LOGS_ENABLED,   // Always log - create directories if needed
	MONITOR_LOGS_DISABLED   // Never log
} logging_mode_enum;

typedef struct monitor_protocol_t
{
	struct brp_protocol_t p;
	FILE * log_file;
	abs_time session_start_timestamp;
	abs_time last_cmd_timestamp;
	abs_time last_time_retrieval;     // last time a timestamp was retrieved
	unsigned log_entry_id;            // used as anchor for html log
	abs_time base_time;               // ms since 1970 to where brp_get_time() was 0
	char * custom_log_path;           // custom log file path (NULL = use default)
	logging_mode_enum logging_mode;   // BRP_LOGS environment variable setting
	unsigned annotation_counter;      // number of open annotations
} * monitor_protocol;

// Anchor format: "_" + hex digits of log_entry_id
#define ANCHOR_FORMAT "_%x"
#define ANCHOR_MAX_SIZE 10


static monitor_protocol get_monitor_protocol(brp_protocol protocol)
{
	for (; protocol != NULL; protocol = protocol->base_protocol) {
		if (protocol->protocol_id == BRP_PROTID_MONITOR)
			return (monitor_protocol) protocol;
	}
	return NULL;
}


static logging_mode_enum parse_brp_logs_env(void)
{
	char env_value[16];
	if (!brp_getenv("BRP_LOGS", env_value, sizeof(env_value)))
		return MONITOR_LOGS_AUTO;

	if (strcmp(env_value, "enabled") == 0)
		return MONITOR_LOGS_ENABLED;
	else if (strcmp(env_value, "disabled") == 0)
		return MONITOR_LOGS_DISABLED;
	return MONITOR_LOGS_AUTO;
}


static abs_time get_abs_time(monitor_protocol protocol)
{
	abs_time now = protocol->base_time + brp_get_time();
	if (now < protocol->last_time_retrieval)
	{
		// rollover of 32bit timer
		protocol->base_time += 0x100000000LL;
		now += 0x100000000LL;
	}
	protocol->last_time_retrieval = now;
	return now;
}


static bool copy_frame(brp_frame dst_frame, brp_frame src_frame)
{
	brp_frame_reader src_frame_rdr;
	brp_frame_read_start(&src_frame_rdr, src_frame);
	brp_frame_read_frm_rest(&src_frame_rdr, dst_frame);
	return brp_frame_read_eof(&src_frame_rdr);
}


static void remove_slash(char * str)
{
	char *src = str, *dst = str;
	while (*src != '\0') {
		if (*src == '/' || *src == '\\')
			dst = str;
		else
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}


static bool is_file_path(const char * path)
{
	if (path == NULL)
		return false;

	size_t path_len = strlen(path);
	if (path_len == 0)
		return false;

	char last_char = path[path_len - 1];
	return (last_char != '/' && last_char != '\\');
}





static bool get_old_format_log_dir_path(time_t date, char * log_dir_path)
{
	char home_dir[PATH_MAX];
	struct tm datetime_struct;
	char datetime_str[11];  // length of "YYYY-MM-DD\0"

	if (! brp_get_home_dir(home_dir))
		return false;

	localtime_r(&date, &datetime_struct);
	strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%d", &datetime_struct);

	if (PATH_MAX <= snprintf(log_dir_path, PATH_MAX,
			"%s/brp-logs-%s/",
			home_dir, datetime_str))
		return false;

	return true;
}


static bool get_default_log_dir_path(time_t date, char * log_dir_path)
{
	char home_dir[PATH_MAX];
	struct tm datetime_struct;
	char datetime_str[11];  // length of "YYYY-MM-DD\0"
	
	if (! brp_get_home_dir(home_dir))
		return false;
	
	localtime_r(&date, &datetime_struct);
	strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%d", &datetime_struct);

	if (PATH_MAX <= snprintf(log_dir_path, PATH_MAX,
			"%s/" BRP_LOG_DIR_PREFIX "%s/",
			home_dir, datetime_str))
		return false;

	return true;
}


static bool get_default_filename(monitor_protocol protocol, char * filename)
{
	char * intf_name;
	struct brp_frame_t instance_id;
	char intf_name_cpy[PATH_MAX];
	char instance_id_cpy[PATH_MAX];

	brp_frame_init(&instance_id);
	if (brp_get_io_id(&protocol->p, &intf_name, &instance_id) != BRP_OK)
	{
		brp_frame_deinit(&instance_id);
		return false;
	}

	strncpy(intf_name_cpy, intf_name, PATH_MAX - 1);
	intf_name_cpy[PATH_MAX - 1] = '\0';
	remove_slash(intf_name_cpy);

	strncpy(instance_id_cpy, (char*)BRP_FRAME_PTR(&instance_id), PATH_MAX - 1);
	instance_id_cpy[PATH_MAX - 1] = '\0';
	remove_slash(instance_id_cpy);

	brp_frame_deinit(&instance_id);

	if (PATH_MAX <= snprintf(filename, PATH_MAX, "%s-%s.html", intf_name_cpy, instance_id_cpy))
		return false;

	return true;
}


static bool get_log_path(monitor_protocol protocol, time_t date, char * log_path)
{
	const char * custom_path = protocol->custom_log_path;
	char log_dir_path[PATH_MAX];
	char filename[PATH_MAX];

	if (protocol->logging_mode == MONITOR_LOGS_DISABLED)
		return false;


	// 1. If custom_path is a file (not a directory) => return it directly
	if (is_file_path(custom_path))
	{
		if (PATH_MAX <= snprintf(log_path, PATH_MAX, "%s", custom_path))
			return false;
		return true;
	}

	// 2. Determine log_dir_path
	if (custom_path != NULL && strlen(custom_path) > 0)
	{
		strncpy(log_dir_path, custom_path, PATH_MAX - 1);
		log_dir_path[PATH_MAX - 1] = '\0';
	}
	else
	{
	// Check for old format directory first (fallback logic)
		char old_dir_path[PATH_MAX];
		if (get_old_format_log_dir_path(date, old_dir_path) &&
		    brp_directory_exists(old_dir_path))
		{
			// Old format directory exists, use it
			strncpy(log_dir_path, old_dir_path, PATH_MAX - 1);
			log_dir_path[PATH_MAX - 1] = '\0';
		}
		else
		{
			// Use new format
			if (! get_default_log_dir_path(date, log_dir_path))
				return false;
		}
	}

	// 3. Generate filename
	if (! get_default_filename(protocol, filename))
		return false;

	// 4. Join log_dir_path + filename
	if (PATH_MAX <= snprintf(log_path, PATH_MAX, "%s%s", log_dir_path, filename))
		return false;

	return true;
}


static void log_file_header(monitor_protocol protocol)
{
	struct tm dt;
	time_t today;
	char * intf_name;
	struct brp_frame_t instance_id;

	brp_frame_init(&instance_id);
	if (brp_get_io_id((brp_protocol)protocol,&intf_name,&instance_id) != BRP_OK)
	{
		brp_frame_write_int8(&instance_id, '?');
		brp_frame_write_int8(&instance_id, '\0');
	}
	time(&today);
	localtime_r(&today, &dt);

	fprintf(protocol->log_file,
			"<!DOCTYPE html>\n"
			"<head>\n"
			"<title>%s on %04i-%02i-%02i</title>\n"
			"<style>\n"
			"body {"
			"	font-family: monospace;"
			"	font-size: 17px;"
			"	margin: 0;"
			"}\n"
			"p {"
			"	text-indent: 13em hanging;"
			"	color: darkgray;"
			"	margin: 0px;"
			"	border: 0.3em solid white;"
			"	display: flow-root;"
			"	scroll-margin-top: 75vh;"
			"}\n"
			"details {"
			"	border-left: 24px solid lightgreen;"
			"	margin: 8px 0 8px 8px;"
			"	> summary {"
			"		cursor: pointer;"
			"		background-color: lightgreen;"
			"		min-height: 24px;"
			"		text-indent: 1em hanging;"
			"		position: sticky;"
			"		top: 0;"
			"		border-bottom: 1px solid white;"
			"	}"
			"}\n"
			"details > summary {"
			"	white-space: pre-line;"
			"	line-height: 1.4em;"
			"}\n"
			"details:not([open]) > summary {"
			"	max-height: 1.4em;"
			"	overflow: hidden;"
			"}\n"
			"details:not([open]) {"
			"	overflow: visible;"
			"	min-height: 24px;"
			"}\n"
			"details > details > summary { top: 25px; }\n"
			"details > details > details > summary { top: 50px; }\n"
			"details > details > details > details > summary { top: 75px; }\n"
			"details:has(> summary.fail) {"
			"	border-color: lightpink;"
			"	> summary {"
			"		background-color: lightpink;"
			"	}"
			"}\n"
			"header {"
			"	position: sticky;"
			"	top: 0;"
			"	background: slategray;"
			"	padding: 10px;"
			"	z-index: 1000;"
			"	border-bottom: 1px solid #ccc;"
			"}\n"
			"header .top-row {"
			"	display: flex;"
			"	align-items: center;"
			"}\n"
			"header h1 {"
			"	margin: 0;"
			"	font-size: 1.2em;"
			"}\n"
			"header .controls {"
			"	display: flex;"
			"	gap: 5px;"
			"	margin-top: 8px;"
			"}\n"
			"header .logo-link {"
			"	margin-left: auto;"
			"}\n"
			"header .logo-link:hover {"
			"	background: transparent;"
			"}\n"
			"header .logo {"
			"	height: 40px;"
			"	cursor: pointer;"
			"}\n"
			"[data-tooltip]:hover::after {"
			"	display: block;"
			"	position: absolute;"
			"	top: 0;"
			"	right: 10px;"
			"	content: attr(data-tooltip);"
			"	background: black;"
			"	color: white;"
			"	padding: .25em;"
			"	border-radius: 5px;"
			"}\n"
			".open, .close {"
			"	background: lightblue;"
			"	border-color: lightblue;"
			"	color: black;"
			"}\n"
			".open {"
			"	margin-top: 3em;"
			"}\n"
			".open a:hover, .close a:hover {"
			"	background: #9FC6D4;"
			"}\n"
			".recv {"
			"	background: white;"
			"}\n"
			".send {"
			"	background: #E0E0E0;"
			"	border-color: #E0E0E0;"
			"}\n"
			".send, .recv {"
			"	color: black;"
			"}\n"
			".break {"
			"	background: mistyrose;"
			"	border-color: mistyrose;"
			"}\n"
			".break a:hover {"
			"	background: #f1d6d3;"
			"}\n"
			".recv a:hover, .poll a:hover {"
			"	background: #efefef;"
			"}\n"
			":target {"
			"	background: yellow;"
			"	border-color: yellow;"
			"}\n"
			":target a:hover, :target a:hover {"
			"	background: #E0E000"
			"}\n"
			"a:first-child {"
			"	display: inline-block;"
			"	width: 13em;"
			"}\n"
			"a:first-child span {"
			"	color: grey;"
			"	margin-left: 1em;"
			"}\n"
			".payload {"
			"	margin-left: 2em;"
			"}\n"
			".delay {"
			"	color: black;"
			"	font-weight: bold;"
			"}\n"
			".to {"
			"	float: right;"
			"	color: grey;"
			"}\n"
			".ok {"
			"	color: #00C000;"
			"	font-weight: bold;"
			"	margin-left: 0;"
			"}\n"
			"a {"
			"	text-decoration: unset;"
			"	color: black;"
			"}\n"
			"a:hover {"
			"	background: #D0D0D0;"
			"}\n"
			".err {"
			"	font-weight: bold;"
			"	color: red;"
			"}\n"
			".cmd {"
			"	font-weight: bold;"
			"}\n"
			".mode {"
			"	background: burlywood;"
			"	border-color: burlywood;"
			"	border-style: solid;"
			"	border-width: 3px 0.8em;"
			"	font-weight: bold;"
			"	border-radius: 4px;"
			"	margin-left: 0.8em;"
			"	margin-right: 0.8em;"
			"}\n"
			"#livemode-toggle {"
			"	display: flex;"
			"	padding: 0;"
			"	border: 1px solid #999;"
			"	cursor: pointer;"
			"}\n"
			"#livemode-toggle .status {"
			"	padding: 5px 10px;"
			"	background: lightgreen;"
			"	animation: blinker 1s linear infinite;"
			"}\n"
			"#livemode-toggle.inactive .status {"
			"	background: lightcoral;"
			"	animation: none;"
			"}\n"
			"#livemode-toggle .action {"
			"	padding: 5px 10px;"
			"	background: #e0e0e0;"
			"}\n"
			"#livemode-toggle:hover .action {"
			"	background: #d0d0d0;"
			"}\n"
			"@keyframes blinker {"
			"	50%% {opacity: 0;}"
			"}\n"
			"article.obj-wrapper:not(:last-of-type) { "
			" border-bottom: solid slategray;"
			" padding-bottom: 0.25em"
			" }\n"
			"article:not(:last-child)>details:not(:has(summary))::before { "
			" content: \"Annotation was not properly closed\";"
			" }\n"
      "article:not(:last-child)>details:not(:has(summary)) {"
      " border-color: orange;"
      " background-color: orange;"
      "}\n"
			"</style>\n"
			"<script type=\"text/javascript\">\n"
			"//<![CDATA[\n"
			"    livemodeToggle = null;\n"
			"    livemodeAction = null;\n"
			"    expandBtn = null;\n"
			"    LIVEMODE_KEY = 'baltech_sdk_monitor_livemode';\n"
			"    window.onload = function(){\n"
			"        livemodeToggle = document.getElementById('livemode-toggle');\n"
			"        livemodeAction = livemodeToggle.querySelector('.action');\n"
			"        expandBtn = document.getElementById('expand-annotations');\n"
			"        if (location.origin !== 'file://' && location.origin !== 'null' &&\n"
			"            location.origin != null)\n"
			"            livemodeToggle.style.display = 'none';\n"
			"        else {\n"
			"            if (sessionStorage.getItem(LIVEMODE_KEY) === 'true')\n"
			"                enableLivemode();\n"
			"            else {\n"
			"                disableLivemode();\n"
			"                if (location.hash === '')\n"
			"                    window.scrollTo(0, document.body.scrollHeight);\n"
			"            }\n"
			"        }\n"
			"    };\n"
			"    function toggleLivemode() {\n"
			"        if (isLivemode())\n"
			"            disableLivemode();\n"
			"        else\n"
			"            enableLivemode();\n"
			"    }\n"
			"    function enableLivemode() {\n"
			"        window.scrollTo(0, document.body.scrollHeight);\n"
			"        livemodeToggle.classList.remove('inactive');\n"
			"        livemodeAction.textContent = 'Deactivate';\n"
			"        expandBtn.disabled = true;\n"
			"        sessionStorage.setItem(LIVEMODE_KEY, 'true');\n"
			"        window.setTimeout(reload, 1000);\n"
			"        if (location.hash !== '')\n"
			"            location.href = location.href.split('#')[0];\n"
			"    }\n"
			"    function disableLivemode() {\n"
			"        livemodeToggle.classList.add('inactive');\n"
			"        livemodeAction.textContent = 'Activate';\n"
			"        expandBtn.disabled = false;\n"
			"        sessionStorage.setItem(LIVEMODE_KEY, 'false');\n"
			"    }\n"
			"    function isLivemode() {\n"
			"        return sessionStorage.getItem(LIVEMODE_KEY) === 'true' && location.hash === '';\n"
			"    }\n"
			"    function reload(){\n"
			"        if (isLivemode() && isAtBottom())\n"
			"            location.replace(location.href.split('#')[0]);\n"
			"        else\n"
			"            disableLivemode();\n"
			"    }\n"
			"    function isAtBottom(){\n"
			"        var d = document;\n"
			"        var docheight = Math.max(\n"
			"            d.body.scrollHeight, d.documentElement.scrollHeight,\n"
			"            d.body.offsetHeight, d.documentElement.offsetHeight,\n"
			"            d.body.clientHeight, d.documentElement.clientHeight);\n"
			"        var winheight =\n"
			"            window.innerHeight || (d.documentElement ||d.body).clientHeight;\n"
			"        var scrolltop = window.pageYOffset ||\n"
			"            (d.documentElement || d.body.parentNode || d.body).scrollTop;\n"
			"        return docheight - winheight - scrolltop < 20;\n"
			"    }\n"
			"    function toggleAnnotations() {\n"
			"        var btn = document.getElementById('expand-annotations');\n"
			"        var expand = btn.textContent === 'Expand All Annotations';\n"
			"        Array.from(document.getElementsByTagName('details')).forEach((e) =>\n"
			"            expand ? e.setAttribute('open', '') : e.removeAttribute('open')\n"
			"        );\n"
			"        btn.textContent = expand ? 'Collapse All Annotations' : 'Expand All Annotations';\n"
			"    }\n"
			"//]]>\n"
			"</script>\n"
			"<link rel=\"icon\" href=\"https://www.baltech.de/favicon.ico\" />\n"
			"</head>\n"
			"<header>\n"
			"    <div class=\"top-row\">\n"
			"        <h1>Monitored Data at %s on %04i-%02i-%02i</h1>\n"
			"        <a href=\"https://www.baltech.de\" target=\"_blank\" class=\"logo-link\">"
			"<img src=\"https://mobile-id.baltech.de/baltech-logo.svg\" class=\"logo\" alt=\"Baltech\" /></a>\n"
			"    </div>\n"
			"    <div class=\"controls\">\n"
			"        <button id=\"expand-annotations\" onclick=\"toggleAnnotations()\" disabled=\"disabled\">"
			"Expand All Annotations</button>\n"
			"        <button id=\"livemode-toggle\" onclick=\"toggleLivemode()\">"
			"<span class=\"status\">Live View</span><span class=\"action\">Deactivate</span></button>\n"
			"    </div>\n"
			"</header>\n"
			"<article>\n",
			BRP_FRAME_PTR(&instance_id),
			dt.tm_year+1900, dt.tm_mon+1, dt.tm_mday,
			BRP_FRAME_PTR(&instance_id),
			dt.tm_year+1900, dt.tm_mon+1, dt.tm_mday);
}

static void log_obj_wrapper(monitor_protocol protocol)
{
	fprintf(protocol->log_file, "</article>\n<article class=\"obj-wrapper\">\n");
}

static void log_entry_start(monitor_protocol protocol,
		char * action, abs_time now)
{
	FILE * log_file = protocol->log_file;
	fprintf(log_file, "<p class=\"%s\" id=\"" ANCHOR_FORMAT "\"><a href=\"#" ANCHOR_FORMAT "\">", action,
			protocol->log_entry_id, protocol->log_entry_id);
	protocol->log_entry_id++;

	time_t now_t = (time_t) (now / 1000);
	char now_str[9];
	strftime(now_str, sizeof(now_str), "%H:%M:%S", localtime(&now_t));
	fprintf(log_file, "%s.%03lld", now_str, now % 1000);
	
	abs_time rel_time = now - protocol->last_cmd_timestamp;
	if (rel_time < 60000)
		fprintf(log_file, " <span>%1lld.%03lld</span>",
				rel_time / 1000, rel_time % 1000);

	fprintf(log_file, "</a>");
}


static void log_errcode(monitor_protocol protocol, brp_errcode errcode)
{
	if (errcode != BRP_OK)
	{
		char * errname = brp_map_errcode(errcode);
		if (errname == NULL)
			fprintf(protocol->log_file,
					"<span class=\"err\">Errcode:0x%08X</span>", errcode);
		else
		{
			char *errurl = brp_map_errcode_to_docurl(errcode);
			// omit prefix "BRP_ERR_" if available
			if (strncmp(errname, "BRP_ERR_", 8) == 0)
				errname += 8;
			if (errurl == NULL)
				fprintf(protocol->log_file,
						"<a class=\"err\" title=\"Errcode:0x%08X\">%s</a>",
						errcode, errname);
			else
			{
				fprintf(protocol->log_file,
						"<a class=\"err\" title=\"Errcode:0x%08X\" "
						    "href=\"%s\">%s</a>",
						errcode, errurl, errname);
			}
		}
	}
}


static void log_frame(monitor_protocol protocol, brp_frame_reader * rdr)
{
	if (!brp_frame_read_eof(rdr) && !brp_frame_read_err(rdr))
	{
		fprintf(protocol->log_file, "%02X", brp_frame_read_int8(rdr));
		while (!brp_frame_read_eof(rdr) && !brp_frame_read_err(rdr))
			fprintf(protocol->log_file, " %02X", brp_frame_read_int8(rdr));
	}
}


static void log_entry_finish(monitor_protocol protocol)
{
	fprintf(protocol->log_file, "</p>\n");
	fflush(protocol->log_file);
}


void log_send_frame(monitor_protocol protocol, unsigned int mode,
		unsigned int cmd_code, brp_errcode errcode, unsigned int timeout,
		brp_frame_reader *rdr)
{
	// log command code
	char * cmd_name = brp_map_cmdcode(cmd_code);
	if (cmd_name == NULL)
		fprintf(protocol->log_file,
				"<span class=\"cmd\">Command Code: 0x%04X</span>", cmd_code);
	else
	{
		char * cmd_docurl = brp_map_cmdcode_to_docurl(cmd_code);
		if (cmd_docurl == NULL)
			fprintf(protocol->log_file,
					"<a class=\"cmd\" title=\"Command Code: %04X\">%s</a>",
					cmd_code, cmd_name);
		else
			fprintf(protocol->log_file,
					"<a class=\"cmd\" title=\"Command Code: 0x%04X\" "
					    "href=\"%s\">%s</a>", cmd_code, cmd_docurl, cmd_name);
	}
	
	// log mode (if available)
	if (mode != BRP_MODE_STD)
	{
		char * mode_str;
		if (mode == BRP_MODE_CONTINUOUS) mode_str = "Continuous";
		else if (mode == BRP_MODE_REPEAT) mode_str = "Repeat";
		else mode_str = "Invalid";
		fprintf(protocol->log_file,
				"<span class=\"mode\">%s Mode</span>", mode_str);
	}
	
	// log payload (if available)
	if (! brp_frame_read_eof(rdr))
	{
		fprintf(protocol->log_file, "<span class=\"payload\">&lt;");
		log_frame(protocol, rdr);
		fprintf(protocol->log_file, "&gt;</span>");
	}
	
	// log errcode (if available)
	if (errcode != BRP_OK)
		log_errcode(protocol, errcode);
	
	// log command timeout
	if (timeout != BRP_INFINITE)
		fprintf(protocol->log_file,
				"<span class=\"to\">(Cmd Timeout: %d.%03ds)</span>",
				timeout / 1000, timeout % 1000);
}


static unsigned to_day(time_t time)
{
	return (unsigned) (time - timezone) / 86400;
}


static bool ensure_log_opened(monitor_protocol protocol, abs_time now)
{
	unsigned today = to_day(now / 1000);
	unsigned day_of_last_cmd = to_day(protocol->last_cmd_timestamp / 1000);
	if (today != day_of_last_cmd || protocol->log_file == NULL)
	{
		char log_path[PATH_MAX];
		time_t now_in_realtime;
		
		if (protocol->log_file != NULL)
		{
			fclose(protocol->log_file);
			protocol->log_file = NULL;
		}
		
		now_in_realtime = now / 1000;
		if (get_log_path(protocol, now_in_realtime, log_path))
		{
			protocol->log_file = fopen(log_path, "a+t");
			if (protocol->log_file != NULL)
			{
				long int file_size;
				fseek(protocol->log_file, 0, SEEK_END);
				file_size = ftell(protocol->log_file);
				if (file_size == 0)
				{
					log_file_header(protocol);
					protocol->log_entry_id = 1;
				}
				else
					protocol->log_entry_id = (unsigned) file_size;

        if(protocol->last_cmd_timestamp == 0)
				  log_obj_wrapper(protocol);
			}
		}
	}

	return protocol->log_file != NULL;
}

static bool ensure_log_dir_exists(monitor_protocol protocol, abs_time now) {
  char log_path[PATH_MAX];
  time_t now_in_realtime = now / 1000;

  if(!get_log_path(protocol, now_in_realtime, log_path))
    return false;

  char log_dir[PATH_MAX];
  strncpy(log_dir, log_path, PATH_MAX - 1);
  log_dir[PATH_MAX - 1] = '\0';

  // Find the last directory separator
  char *last_sep = strrchr(log_dir, '/');
  if (last_sep == NULL)
    last_sep = strrchr(log_dir, '\\');

   if (last_sep != NULL)
   {
     // terminated the path after the last seperator, to ignore the filename
     last_sep += 1;
     *last_sep = '\0';

     if (!brp_create_directory_recursive(log_dir))
       return false;
   }
  return true;
}

static brp_errcode open(monitor_protocol protocol)
{
	abs_time now = get_abs_time(protocol);
	brp_errcode errcode = redirect_open(protocol->p.base_protocol);

	if (protocol->logging_mode == MONITOR_LOGS_ENABLED)
	{
	  if(!ensure_log_dir_exists(protocol, now))
	    return BRP_ERR_OPEN_IO;
	}

	if (ensure_log_opened(protocol, now))
	{
		char proc_name[PATH_MAX];

		if (! brp_get_process_name(proc_name))
			strcpy(proc_name, "?");
		
		log_entry_start(protocol, "open", now);
		if (errcode == BRP_OK)
			fprintf(protocol->log_file, "Connection opened by %s", proc_name);
		else
		{
			log_errcode(protocol, errcode);
			fprintf(protocol->log_file, " Connection open failed by %s", proc_name);
		}
		log_entry_finish(protocol);
	}
	
	protocol->session_start_timestamp = now;
	protocol->last_cmd_timestamp = now;
	return errcode;
}


static brp_errcode close(monitor_protocol protocol)
{
	abs_time now = get_abs_time(protocol);
	brp_errcode errcode = redirect_close(protocol->p.base_protocol);

	if (ensure_log_opened(protocol, now))
	{
		log_entry_start(protocol, "close", now);
		if (errcode == BRP_OK)
			fprintf(protocol->log_file, "Connection closed");
		else
		{
			log_errcode(protocol, errcode);
			fprintf(protocol->log_file, " Connection close failed");
		}
		log_entry_finish(protocol);
		fclose(protocol->log_file);
		protocol->log_file = NULL;
	}
	protocol->session_start_timestamp = now;
	protocol->last_cmd_timestamp = now;
	return errcode;
}


static brp_errcode send_frame(monitor_protocol protocol)
{
	brp_errcode errcode;
	abs_time now;
	unsigned mode, cmd_code, timeout;
	brp_frame_reader rdr;
	
	if (protocol->p.base_protocol == NULL)
		return BRP_ERR_NOT_IMPLEMENTED;
	if(!copy_frame(&protocol->p.base_protocol->send_frame,
			&protocol->p.send_frame))
		return BRP_ERR_OUT_OF_MEMORY;
	
	errcode = brp_send_frame(protocol->p.base_protocol);
	now = get_abs_time(protocol);
	
	brp_frame_read_start(&rdr, &protocol->p.send_frame);
	mode = brp_frame_read_int8(&rdr);
	cmd_code = brp_frame_read_int16(&rdr);
	timeout = brp_frame_read_int32(&rdr);

	if (ensure_log_opened(protocol, now))
	{
		if (brp_frame_read_err(&rdr))
		{
			log_entry_start(protocol, "send", now);
			fprintf(protocol->log_file, "Invalid Frame: ");
			brp_frame_read_start(&rdr, &protocol->p.send_frame);
			log_frame(protocol, &rdr);
			log_errcode(protocol, errcode);
		}
		else if (mode == BRP_MODE_BREAK)
		{
			log_entry_start(protocol, "break", now);
			fprintf(protocol->log_file, "Break Continuous/Repeat Mode");
		}
		else
		{
			log_entry_start(protocol, "send", now);
			log_send_frame(protocol, mode, cmd_code, errcode, timeout, &rdr);
			
		}
		log_entry_finish(protocol);
		
		if (mode != BRP_MODE_BREAK)
			protocol->last_cmd_timestamp = now;
	}
	
	return errcode;
}


static brp_errcode recv_any_frame(monitor_protocol protocol, brp_time timeout)
{
	brp_errcode errcode;
	abs_time now;
	
	errcode = brp_recv_any_frame(protocol->p.base_protocol, timeout);
	now = get_abs_time(protocol);
	if (! copy_frame(&protocol->p.recv_frame,
			&protocol->p.base_protocol->recv_frame))
		return BRP_ERR_OUT_OF_MEMORY;
	
	if (ensure_log_opened(protocol, now))
	{
		log_entry_start(protocol, "recv", now);
		
		if (errcode == BRP_OK)
			fprintf(protocol->log_file, "<span class=\"ok\">OK</span>");
		else
			log_errcode(protocol, errcode);
		
		if (BRP_FRAME_SIZE(&protocol->p.recv_frame) > 0)
		{
			brp_frame_reader rdr;
			fprintf(protocol->log_file, "<span class=\"payload\">&lt;");
			brp_frame_read_start(&rdr, &protocol->p.recv_frame);
			log_frame(protocol, &rdr);
			fprintf(protocol->log_file, "&gt;</span>");
		}
		
		if (timeout != BRP_INFINITE)
			fprintf(protocol->log_file,
					"<span class=\"to\">(Poll Timeout: %ld.%03lds)</span>",
					timeout / 1000, timeout % 1000);
		
		log_entry_finish(protocol);
	}
	
	return errcode;
}


static brp_errcode destroy(monitor_protocol protocol)
{
	// Auto-close any remaining open annotations
	for (unsigned i = 0; i < protocol->annotation_counter; i++)
		brp_annotation_end((brp_protocol)protocol, true, "Auto-close on brp_destroy");

	if (protocol->log_file != NULL)
	{
		fclose(protocol->log_file);
		protocol->log_file = NULL;
	}
	if (protocol->custom_log_path != NULL)
	{
		free(protocol->custom_log_path);
		protocol->custom_log_path = NULL;
	}
	brp_protocol_free((brp_protocol)protocol);
	return BRP_OK;
}


brp_protocol brp_create_monitor(void)
{
	tzset();
	monitor_protocol protocol = (monitor_protocol) brp_protocol_alloc(
		sizeof(struct monitor_protocol_t), BRP_PROTID_MONITOR);
	if (protocol == NULL)
		return NULL;

	protocol->p.cb_open = (brp_cb_generic_t) open;
	protocol->p.cb_send_frame = (brp_cb_generic_t) send_frame;
	protocol->p.cb_recv_any_frame = (brp_cb_recv_any_frame_t) recv_any_frame;
	protocol->p.cb_close = (brp_cb_generic_t) close;
	protocol->p.cb_destroy = (brp_cb_generic_t) destroy;
	protocol->log_file = NULL;
	protocol->session_start_timestamp = 0;
	protocol->last_cmd_timestamp = 0;
	protocol->last_time_retrieval = 0;
	protocol->logging_mode = parse_brp_logs_env();
	protocol->base_time = (time(NULL) * 1000LL) - brp_get_time();
	protocol->annotation_counter = 0;
	return (brp_protocol) protocol;
}


void brp_annotation_start(brp_protocol protocol)
{
	monitor_protocol mon_protocol = get_monitor_protocol(protocol);
	if(mon_protocol == NULL)
	  return;

  if (!ensure_log_opened(mon_protocol, get_abs_time(mon_protocol)))
    return;
  fprintf(mon_protocol->log_file, "<details>\n");
  mon_protocol->annotation_counter++;
}


static void write_escaped_str(FILE * output, const char *str)
{
	int dst_ndx = 0, src_ndx = 0;
	char chr, escaped_str[0x40];
	escaped_str[0] = 0;
	while ((chr = str[src_ndx++]) != 0) {
		if (chr == '&') {
			strcat(escaped_str, "&amp;");
			dst_ndx += 5;  // skip over "&amp;"
		}
		else if (chr == '<') {
			strcat(escaped_str, "&lt;");
			dst_ndx += 4;  // skip over "&lt;"
		}
		else if (chr == '>') {
			strcat(escaped_str, "&gt;");
			dst_ndx += 4;  // skip over "&gt;"
		}
		else {
			escaped_str[dst_ndx] = chr;
			dst_ndx++;
		}
		escaped_str[dst_ndx] = 0;
		
		// ensure that the biggest escapesequence plus zeroterminator fits
		// into escaped_comment. otherwise stop.
		if (dst_ndx > sizeof(escaped_str) - 6)
		{
			fprintf(output, "%s", escaped_str);
			dst_ndx = 0;
		}
	}
	fprintf(output, "%s", escaped_str);
}


void brp_annotation_end(brp_protocol protocol, bool success, char * comment)
{
	monitor_protocol mon_protocol = get_monitor_protocol(protocol);
	if(mon_protocol == NULL)
	  return;

	if(mon_protocol->annotation_counter < 1)
	  return;

  if (!ensure_log_opened(mon_protocol, mon_protocol->last_time_retrieval))
    return;

  time_t now_t = (time_t) (mon_protocol->last_time_retrieval / 1000);
  char now_str[9];
  strftime(now_str, sizeof(now_str), "%H:%M:%S", localtime(&now_t));
  fprintf(mon_protocol->log_file,
      "<summary data-tooltip=\"Contains logs until %s.%03lld\"%s>",
      now_str,
      mon_protocol->last_time_retrieval % 1000,
      success ? "" : " class=\"fail\"");
  write_escaped_str(mon_protocol->log_file, comment);
  fprintf(mon_protocol->log_file, "</summary></details>\n");

  fflush(mon_protocol->log_file);
  mon_protocol->annotation_counter--;
}


brp_errcode brp_set_log_path(brp_protocol protocol, const char * path)
{
	monitor_protocol mon_protocol = get_monitor_protocol(protocol);
	if (mon_protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	if (mon_protocol->custom_log_path != NULL)
	{
		free(mon_protocol->custom_log_path);
		mon_protocol->custom_log_path = NULL;
	}

	if (path != NULL)
	{
		mon_protocol->custom_log_path = malloc(strlen(path) + 1);
		if (mon_protocol->custom_log_path == NULL)
			return BRP_ERR_OUT_OF_MEMORY;
		strcpy(mon_protocol->custom_log_path, path);
	}

	if (mon_protocol->log_file != NULL)
	{
		fclose(mon_protocol->log_file);
		mon_protocol->log_file = NULL;
	}

	// Reset entry ID - will be set correctly when file is actually opened
	mon_protocol->log_entry_id = 0;

	return BRP_OK;
}


brp_errcode brp_get_current_log_anchor(brp_protocol protocol, char ** anchor, brp_mempool * mempool)
{
	char * buf;
	monitor_protocol mon_protocol = get_monitor_protocol(protocol);
	if (mon_protocol == NULL)
		return BRP_ERR_INVALID_API_CALL;

	// Use provided mempool or fall back to protocol's mempool
	if (mempool == NULL)
		mempool = &protocol->mempool;

	// No valid anchor if no log entries written yet
	if (mon_protocol->log_entry_id <= 1)
	{
		*anchor = NULL;
		return BRP_OK;
	}

	buf = (char*) brp_mempool_create_buf(mempool, ANCHOR_MAX_SIZE);
	if (buf == NULL)
		return BRP_ERR_OUT_OF_MEMORY;

	if (ANCHOR_MAX_SIZE <= snprintf(buf, ANCHOR_MAX_SIZE, "#" ANCHOR_FORMAT, mon_protocol->log_entry_id - 1))
		return BRP_ERR_BUFFER_OVERFLOW;

	*anchor = buf;
	return BRP_OK;
}


char * brp_get_log_path(brp_protocol protocol, brp_mempool * mempool)
{
	char log_path_buf[PATH_MAX];
	monitor_protocol mon_protocol = get_monitor_protocol(protocol);
	if (mon_protocol == NULL)
		return NULL;

	// Use provided mempool or fall back to protocol's mempool
	if (mempool == NULL)
		mempool = &protocol->mempool;

	// Get current log path
	if (!get_log_path(mon_protocol, time(NULL), log_path_buf))
		return NULL;

	// Allocate buffer for the result
	size_t path_len = strlen(log_path_buf) + 1; // +1 for null terminator
	char * result_path = (char*) brp_mempool_create_buf(mempool, path_len);
	if (result_path == NULL)
		return NULL;

	// Copy the path
	strcpy(result_path, log_path_buf);
	return result_path;
}

