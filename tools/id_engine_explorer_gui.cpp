#include "reader_helpers.h"
#include "reader_select_dialog.h"

#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFutureWatcher>
#include <QFontDatabase>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QStringList>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QtConcurrent/QtConcurrentRun>

struct CardAnalysisResult
{
	unsigned error;
	reader_card_info card;
};

class ExplorerWindow final : public QWidget
{
public:
	ExplorerWindow()
	{
		setWindowTitle("BALTECH ID-engine Explorer");
		resize(1080, 720);
		setMinimumSize(880, 600);
		buildUi();
	}

	~ExplorerWindow() override
	{
		if (analysisWatcher_ != nullptr)
			analysisWatcher_->waitForFinished();
		if (reader_ != nullptr)
			reader_close(reader_);
	}

private:
	QLabel *connectionLabel_ = nullptr;
	QLabel *firmwareValue_ = nullptr;
	QLabel *configValue_ = nullptr;
	QLabel *serialValue_ = nullptr;
	QLabel *partValue_ = nullptr;
	QLabel *rfidValue_ = nullptr;
	QLabel *functionalValue_ = nullptr;
	QLabel *securityValue_ = nullptr;
	QLabel *healthValue_ = nullptr;
	QTextEdit *log_ = nullptr;
	QPushButton *sampleButton_ = nullptr;
	QPushButton *connectButton_ = nullptr;
	QPushButton *factoryButton_ = nullptr;
	QPushButton *autoreadButton_ = nullptr;
	QPushButton *detailsButton_ = nullptr;
	QPushButton *refreshButton_ = nullptr;
	QFutureWatcher<CardAnalysisResult> *analysisWatcher_ = nullptr;
	QTimer *autoreadTimer_ = nullptr;
	long long selectedSerial_ = 0;
	QString selectedReaderName_;
	reader_handle reader_ = nullptr;

	static QLabel *valueLabel(const QString &text = "Not available")
	{
		auto *label = new QLabel(text);
		label->setWordWrap(true);
		label->setMinimumHeight(30);
		return label;
	}

	static QLabel *descriptionLabel(const QString &text)
	{
		auto *label = new QLabel(text);
		label->setWordWrap(true);
		return label;
	}

	QPushButton *actionButton(const QString &text, const QString &tip)
	{
		auto *button = new QPushButton(text);
		button->setMinimumHeight(36);
		button->setToolTip(tip);
		return button;
	}

	void buildUi()
	{
		auto *root = new QVBoxLayout(this);
		auto *brand = new QLabel("BALTECH  |  balanced technology");
		brand->setObjectName("brand");
		root->addWidget(brand);

		auto *body = new QHBoxLayout;
		root->addLayout(body, 1);
		auto *actions = new QGroupBox("What do you want to do?");
		actions->setMaximumWidth(290);
		auto *actionLayout = new QVBoxLayout(actions);
		sampleButton_ = actionButton("Analyze Sample Card", "Present a card and inspect its detected type and UID.");
		sampleButton_->setEnabled(false);
		actionLayout->addWidget(sampleButton_);
		actionLayout->addWidget(descriptionLabel("Read a card type and UID from the connected reader."));
		auto *configButton = actionButton("Create Configuration", "Configuration authoring requires BALTECH ConfigEditor.");
		configButton->setEnabled(false);
		actionLayout->addWidget(configButton);
		actionLayout->addWidget(descriptionLabel("Configuration authoring is not part of this SDK."));
		auto *updateButton = actionButton("Update Reader", "Open the separate firmware/configuration uploader.");
		actionLayout->addWidget(updateButton);
		actionLayout->addWidget(descriptionLabel("Upload a released firmware/configuration."));
		factoryButton_ = actionButton("Factory Reset", "Restore factory settings and reboot the reader.");
		factoryButton_->setEnabled(false);
		actionLayout->addWidget(factoryButton_);
		actionLayout->addSpacing(10);
		autoreadButton_ = actionButton("Test Autoread Configuration", "Enable autoread once; the reader stops after one card.");
		autoreadButton_->setEnabled(false);
		actionLayout->addWidget(autoreadButton_);
		auto *vhlButton = actionButton("Test VHL File", "VHL file test requires a configured VHL workflow.");
		vhlButton->setEnabled(false);
		actionLayout->addWidget(vhlButton);
		actionLayout->addStretch();
		body->addWidget(actions);

		auto *overview = new QWidget;
		auto *overviewLayout = new QVBoxLayout(overview);
		auto *title = new QLabel("Reader Info at a Glance");
		title->setObjectName("sectionTitle");
		overviewLayout->addWidget(title);

		auto *basics = new QGroupBox("Basics");
		auto *basicsGrid = new QGridLayout(basics);
		firmwareValue_ = valueLabel();
		configValue_ = valueLabel();
		serialValue_ = valueLabel();
		partValue_ = valueLabel();
		basicsGrid->addWidget(new QLabel("Firmware"), 0, 0);
		basicsGrid->addWidget(firmwareValue_, 1, 0);
		basicsGrid->addWidget(new QLabel("Configuration"), 0, 1);
		basicsGrid->addWidget(configValue_, 1, 1);
		basicsGrid->addWidget(new QLabel("Serial Number"), 2, 0);
		basicsGrid->addWidget(serialValue_, 3, 0);
		basicsGrid->addWidget(new QLabel("Article Number"), 2, 1);
		basicsGrid->addWidget(partValue_, 3, 1);
		overviewLayout->addWidget(basics);

		auto *statusGrid = new QGridLayout;
		rfidValue_ = valueLabel();
		functionalValue_ = valueLabel("Use Full Reader Info to inspect supported features.");
		securityValue_ = valueLabel("Not reported by the public SDK API.");
		healthValue_ = valueLabel();
		statusGrid->addWidget(statusGroup("RFID Interface", rfidValue_), 0, 0);
		statusGrid->addWidget(statusGroup("RFID Functional", functionalValue_), 0, 1);
		statusGrid->addWidget(statusGroup("Host Interface Security", securityValue_), 0, 2);
		statusGrid->addWidget(statusGroup("Health", healthValue_), 0, 3);
		overviewLayout->addLayout(statusGrid, 1);

		log_ = new QTextEdit;
		log_->setReadOnly(true);
		log_->setMaximumHeight(100);
		log_->setPlaceholderText("Activity log");
		overviewLayout->addWidget(log_);
		body->addWidget(overview, 1);

		auto *footer = new QHBoxLayout;
		connectButton_ = new QPushButton("Connect Reader");
		refreshButton_ = new QPushButton("Refresh");
		refreshButton_->setEnabled(false);
		detailsButton_ = new QPushButton("Show Full Reader Info");
		detailsButton_->setEnabled(false);
		connectionLabel_ = new QLabel("Disconnected");
		footer->addWidget(connectButton_);
		footer->addWidget(connectionLabel_, 1);
		footer->addWidget(refreshButton_);
		footer->addWidget(detailsButton_);
		root->addLayout(footer);

		connect(refreshButton_, &QPushButton::clicked, this, [this] { refreshInfo(); });
		connect(connectButton_, &QPushButton::clicked, this, [this] { connectReader(); });
		connect(sampleButton_, &QPushButton::clicked, this, [this] { analyzeSampleCard(); });
		connect(detailsButton_, &QPushButton::clicked, this, [this] { showFullInfo(); });
		connect(updateButton, &QPushButton::clicked, this, [this] { openUploader(); });
		connect(factoryButton_, &QPushButton::clicked, this, [this] { factoryReset(); });
		connect(autoreadButton_, &QPushButton::clicked, this, [this] { testAutoread(); });
		autoreadTimer_ = new QTimer(this);
		autoreadTimer_->setInterval(100);
		connect(autoreadTimer_, &QTimer::timeout, this, [this] {
			char message[1024];
			size_t messageLength = 0;
			int messageAvailable = 0;
			const unsigned error = reader_get_autoread_message(reader_, message, sizeof(message), &messageLength, &messageAvailable);
			if (error == 0 && !messageAvailable)
				return;

			autoreadTimer_->stop();
			connectButton_->setEnabled(true);
			sampleButton_->setEnabled(true);
			factoryButton_->setEnabled(true);
			autoreadButton_->setEnabled(true);
			refreshButton_->setEnabled(true);
			detailsButton_->setEnabled(true);
			connectionLabel_->setText("Connected: " + selectedReaderName_);
			if (error != 0)
			{
				const QString errorText = QString("Autoread failed (SDK error 0x%1).").arg(error, 8, 16, QLatin1Char('0'));
				log_->append(errorText);
				QMessageBox::warning(this, "Autoread", errorText);
				return;
			}

			const QString content = QString::fromLocal8Bit(message, static_cast<int>(messageLength));
			log_->append("Autoread card content: " + content);
			connectionLabel_->setText("Autoread card read.");
			QMessageBox::information(this, "Autoread", "Card content:\n" + content);
		});

		setStyleSheet("QWidget { background: #f6f8f9; color: #18252b; font: 10pt 'Noto Sans'; }"
			"QGroupBox { border: 1px solid #c9d2d5; margin-top: 12px; padding: 12px; }"
			"QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 4px; color: #006d69; }"
			"QPushButton { background: #ffffff; border: 1px solid #aebdc1; padding: 7px 10px; }"
			"QPushButton:hover { border-color: #007f78; background: #edf7f6; }"
			"QPushButton:disabled { color: #8b9699; background: #edf0f1; }"
			"QTextEdit { background: white; border: 1px solid #c9d2d5; padding: 5px; }"
			"#brand { color: #17262c; font: bold 20pt 'Noto Sans'; padding: 6px 0; }"
			"#sectionTitle { font: bold 16pt 'Noto Sans'; color: #17262c; }");
	}

	static QGroupBox *statusGroup(const QString &title, QLabel *value)
	{
		auto *group = new QGroupBox(title);
		auto *layout = new QVBoxLayout(group);
		layout->addWidget(value);
		group->setMinimumWidth(125);
		return group;
	}

	void connectReader()
	{
		if (!selectBaltechReader(this, &selectedSerial_, &selectedReaderName_))
			return;
		if (reader_ != nullptr)
		{
			reader_close(reader_);
			reader_ = nullptr;
		}
		reader_ = reader_open(selectedSerial_);
		if (reader_ == nullptr)
		{
			connectionLabel_->setText("Connection failed");
			return;
		}
		connectionLabel_->setText("Connected: " + selectedReaderName_);
		sampleButton_->setEnabled(true);
		factoryButton_->setEnabled(true);
		autoreadButton_->setEnabled(true);
		refreshButton_->setEnabled(true);
		detailsButton_->setEnabled(true);
		log_->append("Reader connected.");
		refreshInfo();
	}

	void analyzeSampleCard()
	{
		if (reader_ == nullptr || analysisWatcher_ != nullptr)
			return;
		connectButton_->setEnabled(false);
		sampleButton_->setEnabled(false);
		factoryButton_->setEnabled(false);
		autoreadButton_->setEnabled(false);
		refreshButton_->setEnabled(false);
		detailsButton_->setEnabled(false);
		connectionLabel_->setText("Scanning for a card...");
		log_->append("Card scan started. Present a card to the reader.");

		auto *watcher = new QFutureWatcher<CardAnalysisResult>(this);
		analysisWatcher_ = watcher;
		connect(watcher, &QFutureWatcher<CardAnalysisResult>::finished, this, [this, watcher] {
			const CardAnalysisResult result = watcher->result();
			if (result.error == 0)
			{
				functionalValue_->setText(QString::fromLocal8Bit(result.card.card_type));
				rfidValue_->setText(QString("%1  UID %2").arg(QString::fromLocal8Bit(result.card.card_type), QString::fromLocal8Bit(result.card.uid)));
				connectionLabel_->setText("Card detected: " + QString::fromLocal8Bit(result.card.card_type));
				log_->append(QString("Card: %1 | UID: %2").arg(QString::fromLocal8Bit(result.card.card_type), QString::fromLocal8Bit(result.card.uid)));
			}
			else
			{
				const QString error = QString::fromLocal8Bit(result.card.error);
				connectionLabel_->setText("Connected: " + selectedReaderName_);
				log_->append("Card scan: " + (error.isEmpty() ? QString("SDK error 0x%1").arg(result.error, 8, 16, QLatin1Char('0')) : error));
			}
			connectButton_->setEnabled(true);
			sampleButton_->setEnabled(true);
			factoryButton_->setEnabled(true);
			autoreadButton_->setEnabled(true);
			refreshButton_->setEnabled(true);
			detailsButton_->setEnabled(true);
			analysisWatcher_ = nullptr;
			watcher->deleteLater();
		});
		watcher->setFuture(QtConcurrent::run([reader = reader_] {
			CardAnalysisResult result{};
			result.error = reader_analyze_sample_card(reader, &result.card);
			return result;
		}));
	}

	void refreshInfo()
	{
		if (reader_ == nullptr)
			return;
		reader_details details{};
		const unsigned error = reader_read_details(reader_, &details);
		if (error != 0)
		{
			connectionLabel_->setText(QString("Reader query failed (SDK error 0x%1)").arg(error, 8, 16, QLatin1Char('0')));
			return;
		}
		firmwareValue_->setText(QString::fromLocal8Bit(details.firmware).trimmed());
		configValue_->setText(QString::fromLocal8Bit(details.configuration).trimmed());
		serialValue_->setText(QString::number(selectedSerial_));
		partValue_->setText(QString("%1  Rev %2").arg(QString::fromLocal8Bit(details.part_number), QString::fromLocal8Bit(details.hardware_revision)).trimmed());
		healthValue_->setText(QString::fromLocal8Bit(details.health));
		rfidValue_->setText(QString::fromLocal8Bit(details.rfid_status));
	}

	void showFullInfo()
	{
		if (reader_ == nullptr)
		{
			QMessageBox::information(this, "Reader information", "Connect a reader first.");
			return;
		}
		reader_details readerInfo{};
		const unsigned detailsError = reader_read_details(reader_, &readerInfo);
		if (detailsError != 0)
		{
			QMessageBox::warning(this, "Full Reader Info", QString("Reader details unavailable (SDK error 0x%1).")
				.arg(detailsError, 8, 16, QLatin1Char('0')));
			return;
		}
		char features[4096] = {};
		const unsigned featureError = reader_read_features(reader_, features, sizeof(features));
		QStringList lines;
		lines << "Connection";
		lines << QString("  Reader: %1").arg(selectedReaderName_);
		lines << "  Interface: USB/HID";
		lines << QString("  Serial number: %1").arg(selectedSerial_);
		lines << "" << "Firmware";
		lines << QString("  %1").arg(QString::fromLocal8Bit(readerInfo.firmware).trimmed());
		lines << "" << "Configuration";
		lines << QString("  RFID configuration: %1").arg(QString::fromLocal8Bit(readerInfo.configuration).trimmed());
		lines << QString("  Device settings: %1").arg(QString::fromLocal8Bit(readerInfo.device_settings).trimmed());
		lines << "" << "Hardware";
		lines << QString("  Article number: %1").arg(QString::fromLocal8Bit(readerInfo.part_number).trimmed());
		lines << QString("  Hardware revision: %1").arg(QString::fromLocal8Bit(readerInfo.hardware_revision).trimmed());
		lines << "" << "Health and boot status";
		lines << QString("  Summary: %1").arg(QString::fromLocal8Bit(readerInfo.health).trimmed());
		lines << QString("  RFID: %1").arg(QString::fromLocal8Bit(readerInfo.rfid_status).trimmed());
		lines << "  Flags:";
		for (const QString &flag : QString::fromLocal8Bit(readerInfo.boot_status).split('\n', Qt::SkipEmptyParts))
			lines << QString("    %1").arg(flag);
		lines << "" << "Supported features";
		if (featureError == 0)
			lines << QString::fromLocal8Bit(features).trimmed().split('\n', Qt::SkipEmptyParts);
		else
			lines << QString("  Unavailable (SDK error 0x%1)").arg(featureError, 8, 16, QLatin1Char('0'));

		QDialog dialog(this);
		dialog.setWindowTitle("Full Reader Info");
		dialog.resize(720, 620);
		auto *layout = new QVBoxLayout(&dialog);
		auto *text = new QTextEdit;
		text->setReadOnly(true);
		text->setLineWrapMode(QTextEdit::NoWrap);
		text->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
		text->setPlainText(lines.join('\n'));
		layout->addWidget(text);
		auto *buttons = new QDialogButtonBox(QDialogButtonBox::Close);
		connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
		connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
		layout->addWidget(buttons);
		dialog.exec();
	}

	void openUploader()
	{
		const QString executable = QApplication::applicationDirPath() + "/baltech_firmware_uploader_gui";
		if (!QProcess::startDetached(executable, {}))
			QMessageBox::warning(this, "Uploader", "Could not start the uploader GUI. Build baltech_firmware_uploader_gui first.");
	}

	void factoryReset()
	{
		if (reader_ == nullptr)
			return;
		const auto answer = QMessageBox::warning(this, "Factory Reset",
			"This restores factory settings and reboots the reader. Continue?",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
		if (answer != QMessageBox::Yes)
			return;
		const unsigned error = reader_factory_reset(reader_);
		if (error != 0)
			QMessageBox::critical(this, "Factory Reset", QString("SDK error 0x%1").arg(error, 8, 16, QLatin1Char('0')));
		else
			log_->append("Factory reset started; reader is rebooting.");
	}

	void testAutoread()
	{
		if (reader_ == nullptr)
			return;
		const unsigned error = reader_enable_autoread_once(reader_);
		if (error != 0)
			QMessageBox::warning(this, "Autoread", QString("Could not start autoread (SDK error 0x%1).").arg(error, 8, 16, QLatin1Char('0')));
		else
		{
			connectButton_->setEnabled(false);
			sampleButton_->setEnabled(false);
			factoryButton_->setEnabled(false);
			autoreadButton_->setEnabled(false);
			refreshButton_->setEnabled(false);
			detailsButton_->setEnabled(false);
			connectionLabel_->setText("Waiting for a card...");
			log_->append("Autoread started. Present a card to the reader.");
			autoreadTimer_->start();
		}
	}
};

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	ExplorerWindow window;
	window.show();
	return application.exec();
}