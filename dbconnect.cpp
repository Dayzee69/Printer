#include "dbconnect.h"
#include <mainwindow.h>
#include <QMessageBox>
#include <QSqlError>

DBConnect::DBConnect()
{

}
void DBConnect::connOpen()
{


    QFile file("database.txt");

    file.open(QIODevice::ReadOnly);
    QStringList dbList;
    int i = 0;
    while(!file.atEnd())
    {
        dbList << file.readLine();

        QStringList strList = dbList[i].split(":");
        dbList[i]=strList[1].remove("\r\n");
        i++;
    }

    mydb = QSqlDatabase::addDatabase("QODBC3");
    mydb.setDatabaseName("DRIVER={ODBC Driver 17 for SQL Server};SERVER="+dbList[0]+"\\SQLEXPRESS;DATABASE="+dbList[1]+";");
    mydb.setUserName(dbList[2]);
    mydb.setPassword(dbList[3]);

    if(!mydb.open())
    {
        throw std::runtime_error("Не удалось подключится с базе данных");
    }

}
void DBConnect::connClose(){
    mydb.close();
}
