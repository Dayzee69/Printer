#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbconnect.h"
#include "updatewindow.h"
#include "addwindow.h"
#include "addprinterwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotCustomMenuRequested(QPoint pos);
    void slotUptade();
    void on_action_2_triggered();
    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    void ReadDB();
    void ReadDBadd();
    void ReadDBup();

};
#endif // MAINWINDOW_H
