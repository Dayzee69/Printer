#ifndef THREADWINDOW_H
#define THREADWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QThread>

class threadwindow : public QThread
{
public:
    threadwindow();
    void run();
};

#endif // THREADWINDOW_H
