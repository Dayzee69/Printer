#include "addprinterwindow.h"
#include "ui_addprinterwindow.h"
#include <QMessageBox>

AddPrinterWindow::AddPrinterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPrinterWindow)
{
    ui->setupUi(this);

    ui->departCB->addItem("Правление");
    ui->departCB->addItem("Бухгалтерия");
    ui->departCB->addItem("Юридический отдел");
    ui->departCB->addItem("Отдел развития");
    ui->departCB->addItem("Отдел финансового мониторинга");
    ui->departCB->addItem("Операционно - кассового упавления");
    ui->departCB->addItem("АХО");
    ui->departCB->addItem("Коммерческий отдел");
    ui->departCB->addItem("Отдел автоматизации");
    ui->departCB->addItem("Служба внутреннего контроля");
    conn.connOpen();
    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT  id, Name FROM Cartriges ORDER BY id");

    while (query->next()) {
            ui->cartrigeCB->addItem(query->value(1).toString(), query->value(0));
    }
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

AddPrinterWindow::~AddPrinterWindow()
{
    conn.connClose();
    delete ui;
}

void AddPrinterWindow::GetInfo()
{
    if(ui->nameLine->text() == "")
    {
        throw std::runtime_error("Все поля обязательны для заполнения");
    }

    QString nameStr = ui->nameLine->text();
    QString departStr = ui->departCB->currentText();
    QString cartrigeStr = ui->cartrigeCB->currentData().toString();
    AddInfo(nameStr, departStr, cartrigeStr);
}

void AddPrinterWindow::AddInfo(QString name,QString depart, QString cartrige)
{

    QSqlQuery *query = new QSqlQuery();
         query->prepare("INSERT INTO Printers (Name, Department, Cartrige_ID) "
                       "VALUES (?, ?, ?)");
         query->addBindValue(name);
         query->addBindValue(depart);
         query->addBindValue(cartrige);
         query->exec();

}

void AddPrinterWindow::on_addButton_clicked()
{
    try
    {
        GetInfo();
        this->close();
    }
    catch(QException &ex)
    {
        QMessageBox::warning(this, "Исключение", ex.what());
    }
}
