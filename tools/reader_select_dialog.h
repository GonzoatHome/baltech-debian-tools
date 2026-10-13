#ifndef BALTECH_READER_SELECT_DIALOG_H
#define BALTECH_READER_SELECT_DIALOG_H

#include <QString>
#include <QWidget>

bool selectBaltechReader(QWidget *parent, long long *serial, QString *readerName);

#endif