#include "addwindow.h"
#include "ui_addwindow.h"
#include <QException>
#include <QMessageBox>

AddWindow::AddWindow( QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWindow)
{
    ui->setupUi(this);
        setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

}

AddWindow::~AddWindow()
{
    delete ui;
}

void AddWindow::GetInfo()
{
    if(ui->nameLine->text() == "" || ui->amoundLine->text() == "")
    {
        throw std::runtime_error("Все поля обязательны для заполнения");
    }

    QString nameStr = ui->nameLine->text();
    int amound = ui->amoundLine->text().toInt();
    AddInfo(nameStr, amound);
}

void AddWindow::AddInfo(QString name,int amound)
{
    DBConnect conn;
    conn.connOpen();
    QSqlQuery *query = new QSqlQuery();
         query->prepare("INSERT INTO Cartriges (Name, Amound) "
                       "VALUES (?, ?)");
         query->addBindValue(name);
         query->addBindValue(amound);
         query->exec();
         conn.connClose();
}

void AddWindow::on_addButton_clicked()
{
    try {
        GetInfo();
        this->close();
    } catch (std::exception& ex) {
        QMessageBox::warning(this, "Исключение", ex.what());
    }
}
