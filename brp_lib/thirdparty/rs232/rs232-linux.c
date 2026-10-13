/*
    Cross-platform serial / RS232 library
    Version 0.21, 11/10/2015
    -> LINUX and MacOS implementation
    -> rs232-linux.c

    The MIT License (MIT)

    Copyright (c) 2013-2015 Frédéric Meslin, Florent Touchard
    Email: fredericmeslin@hotmail.com
    Website: www.fredslab.net
    Twitter: @marzacdev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
  
*/

#if defined(__unix__) || defined(__unix) || \
    defined(__APPLE__) && defined(__MACH__)

#define _DARWIN_C_SOURCE

#include "rs232.h"

#include <unistd.h>
#if !defined(__USE_MISC)
    #define __USE_MISC // For CRTSCTS
#endif
#include <termios.h>
#include <fcntl.h>
#include <dirent.h>

#if !defined(__USE_SVID)
    #define __USE_SVID // For strdup
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

/*****************************************************************************/
/** Base name for COM devices */
#if defined(__APPLE__) && defined(__MACH__)
    static const char * devBases[] = {
        "tty."
    };
#else
    static const char * devBases[] = {
        "ttyACM", "ttyUSB", "rfcomm", "ttyS"
    };
#endif
#define DEV_BASES_CNT     (sizeof(devBases)/sizeof(const char *))


struct comPortList_t
{
    const char * internalName;
    struct comPortList_t * next;
};

struct comPort_t
{
    int handle;
};


/*****************************************************************************/
/** Private functions */
int _BaudFlag(int BaudRate);

/*****************************************************************************/
int comEnumerate(comPortList * portList)
{
    int noDevices = 0;
    *portList = NULL;
    for (int i = 0; i < DEV_BASES_CNT; i++)
    {
        size_t baseLen = strlen(devBases[i]);
        struct dirent * dp;
    // Enumerate devices
        DIR * dirp = opendir("/dev");
        while ((dp = readdir(dirp)) != NULL) {
            if (strncmp(devBases[i], dp->d_name, baseLen) == 0) {
                comPortList newEntry = malloc(sizeof(struct comPortList_t));
                char * internalName = (char *) malloc(5+strlen(dp->d_name)+1);
                if (newEntry == NULL  ||  internalName == NULL)
                {
                    free(newEntry);
                    free((void*)internalName);
                    comFreePortList(*portList);
                    return 0;
                }
                strcpy(internalName, "/dev/");
                strcat(internalName, dp->d_name);
                newEntry->internalName = internalName;
                newEntry->next = *portList;
                *portList  = newEntry;
                noDevices++;
            }
        }
        closedir(dirp);
    }
    return noDevices;
}

void comFreePortList(comPortList portList)
{
    while (portList != NULL)
    {
        comPortList delEntry = portList;
        portList = portList->next;
        free((void*)delEntry->internalName);
        free(delEntry);
    }
}

const char * comGetNextPortName(comPortList * portListIter)
{
    comPortList curEntry = *portListIter;
    if (*portListIter == NULL)
        return NULL;
    *portListIter = curEntry->next;
    return curEntry->internalName + 5;    // skip "/dev/"
}

const char * comGetNextFullName(comPortList * portListIter)
{
    comPortList curEntry = *portListIter;
    if (*portListIter == NULL)
        return NULL;
    *portListIter = curEntry->next;
    return curEntry->internalName;
}

/*****************************************************************************/
comPort comOpen(const char * portName, int baudrate, int parity)
{
    comPort newEntry;
    int handle;
    char * fullPortName = NULL;
    if (strncmp(portName, "/dev/", 5) != 0)
    {
        fullPortName = malloc(5 + strlen(portName) + 1);
        if (fullPortName == NULL)
            return NULL;
        strcpy(fullPortName, "/dev/");
        strcat(fullPortName, portName);
        portName = fullPortName;
    }
// Open port
    handle = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
    free(fullPortName);
    if (handle < 0)
        return NULL;
// General configuration
    struct termios config;
    memset(&config, 0, sizeof(config));
    tcgetattr(handle, &config);
    config.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
    config.c_iflag |= IGNPAR | IGNBRK;
    config.c_oflag &= ~(OPOST | ONLCR | OCRNL);
    config.c_cflag &= ~(PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS);
    config.c_cflag |= CLOCAL | CREAD | CS8;
    config.c_lflag &= ~(ICANON | ISIG | ECHO);
    switch (parity)
    {
        case PARITY_NONE:  break;
        case PARITY_ODD:   config.c_cflag |= PARENB|PARODD; break;
        case PARITY_EVEN:  config.c_cflag |= PARENB; break;
#if !defined(_DARWIN_C_SOURCE)
        case PARITY_SPACE: config.c_cflag |= PARENB|CMSPAR; break;
        case PARITY_MARK:  config.c_cflag |= PARENB|CMSPAR|PARODD; break;
#endif
    }
    int flag = _BaudFlag(baudrate);
    cfsetospeed(&config, flag);
    cfsetispeed(&config, flag);
// Timeouts configuration
    config.c_cc[VTIME] = 1;
    config.c_cc[VMIN]  = 0;
    //fcntl(handle, F_SETFL, FNDELAY);
// Validate configuration and reserve memory for handle
    newEntry = malloc(sizeof(struct comPort_t));
    if (tcsetattr(handle, TCSANOW, &config) < 0  ||  newEntry == NULL) {
        close(handle);
        free(newEntry);
        return NULL;
    }
    newEntry->handle = handle;
    return newEntry;
}

void comClose(comPort port)
{
    tcdrain(port->handle);
    close(port->handle);
    free(port);
}

/*****************************************************************************/
int comWrite(comPort port, const char * buffer, size_t len)
{
    int res = (int) write(port->handle, buffer, len);
    if (res < 0)
        res = 0;
    return res;
}

int comRead(comPort port, char * buffer, size_t len)
{
    int res = (int) read(port->handle, buffer, len);
    if (res < 0)
        res = 0;
    return res;
}

int comReadBlocking(comPort port, char * buffer, size_t len, unsigned timeout, unsigned interbyte_timeout_ms)
{
    fd_set set;
    struct timeval to;
    int rv, res;

    // Note: interbyte_timeout_ms parameter accepted for API consistency with Windows,
    // but not used in Linux implementation as the issue doesn't occur on this platform.
    (void)interbyte_timeout_ms;  // Suppress unused parameter warning

    FD_ZERO(&set); /* clear the set */
    FD_SET(port->handle, &set);

    to.tv_sec = timeout / 1000;
    to.tv_usec = (timeout % 1000) * 1000;

    rv = select(port->handle + 1, &set, NULL, NULL, &to);
    if(rv <= 0)
        return 0;
    res = (int) read(port->handle, buffer, len);
    if (res < 0)
        res = 0;
    return res;
}

/*****************************************************************************/
int _BaudFlag(int BaudRate)
{
    switch(BaudRate)
    {
        case 50:      return B50; break;
        case 110:     return B110; break;
        case 134:     return B134; break;
        case 150:     return B150; break;
        case 200:     return B200; break;
        case 300:     return B300; break;
        case 600:     return B600; break;
        case 1200:    return B1200; break;
        case 1800:    return B1800; break;
        case 2400:    return B2400; break;
        case 4800:    return B4800; break;
        case 9600:    return B9600; break;
        case 19200:   return B19200; break;
        case 38400:   return B38400; break;
        case 57600:   return B57600; break;
        case 115200:  return B115200; break;
        case 230400:  return B230400; break;
#if defined(B500000)
        case 500000: return B500000; break;
        case 576000: return B576000; break;
        case 921600: return B921600; break;
        case 1000000: return B1000000; break;
        case 1152000: return B1152000; break;
        case 1500000: return B1500000; break;
        case 2000000: return B2000000; break;
        case 2500000: return B2500000; break;
        case 3000000: return B3000000; break;
        case 3500000: return B3500000; break;
        case 4000000: return B4000000; break;
#endif
        default : return B0; break;
    }
}

int comSetDtr(comPort port, int state)
{
    int cmd = state ? TIOCMBIS : TIOCMBIC;
    int flag = TIOCM_DTR;
    return ioctl(port->handle, cmd, &flag) != -1;
}


int comSetRts(comPort port, int state)
{
    int cmd = state ? TIOCMBIS : TIOCMBIC;
    int flag = TIOCM_RTS;
    return ioctl(port->handle, cmd, &flag) != -1;
}


#endif // unix
