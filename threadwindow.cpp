#include "threadwindow.h"
#include <QTime>
#include <QMessageBox>
#include <QDebug>

threadwindow::threadwindow()
{

}


void threadwindow::run()
{

    QTime time;
    QString strTime;
    QString strTime2 = "13:06:00";
    qDebug()<<time.currentTime().toString();
    while(true)
    {
        strTime = time.currentTime().toString();
        if(strTime == strTime2)
        {

        }
    }

}
