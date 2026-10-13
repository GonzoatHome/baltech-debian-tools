#include "reader_helpers.h"
#include "reader_select_dialog.h"

#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QTextCursor>
#include <QTextEdit>
#include <QVBoxLayout>

class UploaderWindow final : public QWidget
{
public:
	UploaderWindow()
	{
		setWindowTitle("BALTECH Firmware / Configuration Uploader");
		resize(740, 620);
		setMinimumSize(620, 600);
		buildUi();
	}

private:
	QLineEdit *filePath_ = nullptr;
	QLabel *readerLabel_ = nullptr;
	QLabel *status_ = nullptr;
	QLabel *modeStatus_ = nullptr;
	QTextEdit *outputLog_ = nullptr;
	QProgressBar *progress_ = nullptr;
	QPushButton *startButton_ = nullptr;
	QRadioButton *wired_ = nullptr;
	QRadioButton *wireless_ = nullptr;
	QRadioButton *configCard_ = nullptr;
	long long selectedSerial_ = 0;
	QString selectedReaderName_;
	QProcess process_;

	void buildUi()
	{
		auto *root = new QVBoxLayout(this);
		auto *brand = new QLabel("BALTECH  |  balanced technology");
		brand->setObjectName("brand");
		root->addWidget(brand);

		auto *fileGroup = new QGroupBox("Select Firmware / Configuration");
		auto *fileLayout = new QHBoxLayout(fileGroup);
		filePath_ = new QLineEdit;
		filePath_->setReadOnly(true);
		filePath_->setPlaceholderText("Choose a BEC / BEC2 / BF3 configuration or firmware file");
		auto *browse = new QPushButton("Browse...");
		fileLayout->addWidget(filePath_, 1);
		fileLayout->addWidget(browse);
		root->addWidget(fileGroup);

		auto *readerGroup = new QGroupBox("Target reader");
		auto *readerLayout = new QHBoxLayout(readerGroup);
		readerLabel_ = new QLabel("No reader selected");
		auto *selectReader = new QPushButton("Select Reader...");
		readerLayout->addWidget(readerLabel_, 1);
		readerLayout->addWidget(selectReader);
		root->addWidget(readerGroup);

		auto *modes = new QGroupBox("What do you want to do?");
		modes->setMinimumHeight(132);
		modes->setMaximumHeight(132);
		auto *modeLayout = new QHBoxLayout(modes);
		wired_ = modeCard("Upload to a\nconnected reader", "Start Wired Upload");
		wireless_ = modeCard("Upload wirelessly\nto another reader", "Start Wireless Upload");
		wired_->setChecked(true);
		modeLayout->addWidget(wired_);
		modeLayout->addWidget(wireless_);
		root->addWidget(modes);
		root->addSpacing(12);

		modeStatus_ = new QLabel("Wired upload uses the BALTECH SDK updater.");
		modeStatus_->setWordWrap(true);
		root->addWidget(modeStatus_);
		progress_ = new QProgressBar;
		progress_->setRange(0, 100);
		progress_->setValue(0);
		root->addWidget(progress_);
		status_ = new QLabel("Ready");
		root->addWidget(status_);
		outputLog_ = new QTextEdit;
		outputLog_->setReadOnly(true);
		outputLog_->setMinimumHeight(48);
		outputLog_->setMaximumHeight(115);
		outputLog_->setPlaceholderText("Upload details and SDK errors appear here.");
		root->addWidget(outputLog_);
		startButton_ = new QPushButton("Start Wired Upload");
		startButton_->setMinimumHeight(38);
		root->addWidget(startButton_);

		connect(browse, &QPushButton::clicked, this, [this] { chooseFile(); });
		connect(selectReader, &QPushButton::clicked, this, [this] { chooseReader(); });
		connect(wired_, &QRadioButton::clicked, this, [this] { selectWired(); });
		connect(wireless_, &QRadioButton::clicked, this, [this] { unavailableMode("Wireless upload is not implemented by the available SDK updater."); });
		connect(startButton_, &QPushButton::clicked, this, [this] { startUpload(); });
		connect(&process_, &QProcess::readyReadStandardOutput, this, [this] { processOutput(); });
		connect(&process_, &QProcess::readyReadStandardError, this, [this] {
			const QString error = QString::fromLocal8Bit(process_.readAllStandardError()).trimmed();
			if (!error.isEmpty())
			{
				appendOutput("ERROR: " + error + "\n");
				status_->setText(error.section('\n', -1).trimmed());
			}
		});
		connect(&process_, &QProcess::finished, this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
			startButton_->setEnabled(true);
			if (exitStatus == QProcess::NormalExit && exitCode == 0)
			{
				status_->setText("Upload complete");
				progress_->setValue(100);
			}
			else
			{
				const QString failure = QString("Upload failed (exit code %1).").arg(exitCode);
				status_->setText(failure);
				appendOutput(failure + "\n");
			}
		});

		setStyleSheet("QWidget { background: #f6f8f9; color: #18252b; font: 10pt 'Noto Sans'; }"
			"QGroupBox { border: 1px solid #c9d2d5; margin-top: 12px; padding: 12px; }"
			"QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 4px; color: #006d69; }"
			"QPushButton { background: #ffffff; border: 1px solid #aebdc1; padding: 7px 12px; }"
			"QPushButton:hover { border-color: #007f78; background: #edf7f6; }"
			"QPushButton:disabled { color: #8b9699; background: #edf0f1; }"
			"QLineEdit { background: white; border: 1px solid #c9d2d5; padding: 6px; }"
			"#brand { color: #17262c; font: bold 20pt 'Noto Sans'; padding: 6px 0; }");
	}

	QRadioButton *modeCard(const QString &description, const QString &buttonText)
	{
		auto *card = new QRadioButton(description + "\n" + buttonText);
		card->setFixedHeight(82);
		card->setStyleSheet("QRadioButton { border: 1px solid #d0d8da; background: white; padding: 6px; }"
			"QRadioButton:checked { border: 2px solid #007f78; background: #edf7f6; }");
		return card;
	}

	void chooseFile()
	{
		const QString path = QFileDialog::getOpenFileName(this, "Select firmware or configuration",
			QString(), "BALTECH files (*.bec *.bec2 *.bf3 *.hex);;All files (*)");
		if (!path.isEmpty())
			filePath_->setText(path);
	}

	void chooseReader()
	{
		long long serial = 0;
		QString readerName;
		if (!selectBaltechReader(this, &serial, &readerName))
			return;
		selectedSerial_ = serial;
		selectedReaderName_ = readerName;
		readerLabel_->setText(QString("%1 | SN %2").arg(readerName).arg(serial, 8, 10, QLatin1Char('0')));
		status_->setText("Reader selected.");
	}

	void selectWired()
	{
		startButton_->setEnabled(true);
		startButton_->setText("Start Wired Upload");
		modeStatus_->setText("Wired upload uses the BALTECH SDK updater.");
	}

	void unavailableMode(const QString &message)
	{
		startButton_->setEnabled(false);
		modeStatus_->setText(message);
	}

	void startUpload()
	{
		if (filePath_->text().isEmpty() || !QFileInfo::exists(filePath_->text()))
		{
			QMessageBox::information(this, "Firmware file", "Select an existing firmware/configuration file first.");
			return;
		}
		if (selectedSerial_ == 0)
		{
			QMessageBox::information(this, "Reader", "Select a USB/HID reader first.");
			return;
		}
		const auto answer = QMessageBox::warning(this, "Confirm configuration / firmware upload",
			QString("Upload '%1' to reader SN %2? Keep the reader connected during upload.")
				.arg(QFileInfo(filePath_->text()).fileName())
				.arg(selectedSerial_, 8, 10, QLatin1Char('0')),
			QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
		if (answer != QMessageBox::Yes)
			return;

		const QString cliPath = QApplication::applicationDirPath() + "/baltech_firmware_uploader";
		process_.setProgram(cliPath);
		process_.setArguments({"--serial", QString::number(selectedSerial_), "--yes", filePath_->text()});
		progress_->setValue(0);
		outputLog_->clear();
		status_->setText("Starting wired upload...");
		startButton_->setEnabled(false);
		process_.start();
		if (!process_.waitForStarted(3000))
		{
			startButton_->setEnabled(true);
			status_->setText("Could not start the CLI uploader. Build baltech_firmware_uploader first.");
		}
	}

	void processOutput()
	{
		QString output = QString::fromLocal8Bit(process_.readAllStandardOutput());
		if (output.isEmpty())
			return;
		appendOutput(output);
		output.replace('\r', '\n');
		status_->setText(output.section('\n', -1).trimmed());
		const qsizetype percentMark = output.lastIndexOf('%');
		if (percentMark <= 0)
			return;
		qsizetype start = percentMark - 1;
		while (start >= 0 && output.at(start).isDigit())
			start--;
		bool valid = false;
		const int percent = output.mid(start + 1, percentMark - start - 1).toInt(&valid);
		if (valid)
			progress_->setValue(qBound(0, percent, 100));
	}

	void appendOutput(const QString &text)
	{
		outputLog_->moveCursor(QTextCursor::End);
		outputLog_->insertPlainText(text);
		outputLog_->ensureCursorVisible();
	}
};

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	UploaderWindow window;
	window.show();
	return application.exec();
}