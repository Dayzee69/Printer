#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include <QWidget>
#include "dbconnect.h"


namespace Ui {
class UpdateWindow;
}

class UpdateWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateWindow(int iD, QWidget *parent = nullptr);
    ~UpdateWindow();

private slots:
    void on_updateButton_clicked();
    void on_cartrigeCB_currentTextChanged(const QString &arg1);


private:
    Ui::UpdateWindow *ui;
    void UpdateInfo();
    void UpdateDB();
    DBConnect conn;
};

#endif // UPDATEWINDOW_H
