#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QWidget>
#include "dbconnect.h"

namespace Ui {
class AddWindow;
}

class AddWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddWindow(QWidget *parent = nullptr);
    ~AddWindow();

private slots:
    void on_addButton_clicked();

private:
    Ui::AddWindow *ui;
    void GetInfo();
    void AddInfo(QString name,int amound);
};

#endif // ADDWINDOW_H
