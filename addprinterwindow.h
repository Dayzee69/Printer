#ifndef ADDPRINTERWINDOW_H
#define ADDPRINTERWINDOW_H

#include <QWidget>
#include "dbconnect.h"


namespace Ui {
class AddPrinterWindow;
}

class AddPrinterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddPrinterWindow(QWidget *parent = nullptr);
    ~AddPrinterWindow();

private slots:
    void on_addButton_clicked();

private:
    Ui::AddPrinterWindow *ui;
    void GetInfo();
    void AddInfo(QString name, QString depart, QString cartrige);
    DBConnect conn;
};

#endif // ADDPRINTERWINDOW_H
