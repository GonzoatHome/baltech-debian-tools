#include "reader_select_dialog.h"
#include "reader_helpers.h"

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

class ReaderSelectDialog final : public QDialog
{
public:
	ReaderSelectDialog(QWidget *parent, long long *serial, QString *readerName)
		: QDialog(parent), serial_(serial), readerName_(readerName)
	{
		setWindowTitle("Explorer");
		setMinimumSize(430, 320);
		auto *layout = new QVBoxLayout(this);
		layout->addWidget(new QLabel("Please select a reader"));

		table_ = new QTableWidget(0, 2);
		table_->setHorizontalHeaderLabels({"Serial Number", "Protocol"});
		table_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		table_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
		table_->setSelectionBehavior(QAbstractItemView::SelectRows);
		table_->setSelectionMode(QAbstractItemView::SingleSelection);
		table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
		layout->addWidget(table_, 1);
		auto *emptyState = new QLabel("No BALTECH USB/HID readers found.");
		emptyState->setObjectName("emptyState");
		layout->addWidget(emptyState);

		auto *printMgmt = new QCheckBox("Show print-mgmt readers with alternative USB keyboard settings");
		printMgmt->setEnabled(false);
		printMgmt->setToolTip("This reader category is not exposed by the public SDK USB/HID iterator.");
		layout->addWidget(printMgmt);

		auto *searchOptions = new QPushButton("Show Search Options");
		searchOptions->setFlat(true);
		searchOptions->setStyleSheet("QPushButton { color: #006d69; text-align: left; text-decoration: underline; padding: 0; }");
		layout->addWidget(searchOptions);

		auto *buttons = new QDialogButtonBox(QDialogButtonBox::Cancel);
		selectButton_ = buttons->addButton("Select", QDialogButtonBox::AcceptRole);
		selectButton_->setEnabled(false);
		layout->addWidget(buttons);
		connect(table_, &QTableWidget::itemSelectionChanged, this, [this] {
			selectButton_->setEnabled(table_->currentRow() >= 0);
		});
		connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
		connect(selectButton_, &QPushButton::clicked, this, [this] { acceptSelection(); });
		connect(searchOptions, &QPushButton::clicked, this, [this] {
			QMessageBox::information(this, "Search Options", "The SDK enumerates BALTECH USB/HID BRP readers with numeric serial numbers.");
		});
		populate(emptyState);
	}

private:
	QTableWidget *table_ = nullptr;
	QPushButton *selectButton_ = nullptr;
	long long *serial_;
	QString *readerName_;

	void populate(QLabel *emptyState)
	{
		reader_entry *entries = nullptr;
		size_t count = 0;
		if (!reader_enumerate_devices(&entries, &count))
		{
			emptyState->setText("Reader enumeration failed.");
			return;
		}
		table_->setRowCount(static_cast<int>(count));
		for (size_t index = 0; index < count; index++)
		{
			const int row = static_cast<int>(index);
			const auto serialItem = new QTableWidgetItem(QString::number(entries[index].serial));
			serialItem->setData(Qt::UserRole, QVariant::fromValue<qlonglong>(entries[index].serial));
			table_->setItem(row, 0, serialItem);
			table_->setItem(row, 1, new QTableWidgetItem(QString::fromLocal8Bit(entries[index].name) + " (USB/HID)"));
		}
		reader_free_devices(entries);
		emptyState->setVisible(count == 0);
	}

	void acceptSelection()
	{
		const int row = table_->currentRow();
		if (row < 0)
			return;
		*serial_ = table_->item(row, 0)->data(Qt::UserRole).toLongLong();
		*readerName_ = table_->item(row, 1)->text();
		accept();
	}
};

bool selectBaltechReader(QWidget *parent, long long *serial, QString *readerName)
{
	if (serial == nullptr || readerName == nullptr)
		return false;
	ReaderSelectDialog dialog(parent, serial, readerName);
	return dialog.exec() == QDialog::Accepted;
}