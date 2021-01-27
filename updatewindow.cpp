#include "updatewindow.h"
#include "ui_updatewindow.h"
#include <QMessageBox>

struct Obj
{
    int id;
    QString name;
    QString depart;
    QString cartrige;
    int amound;
};
Obj *obj = new Obj;
UpdateWindow::UpdateWindow(int ID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateWindow)
{
    ui->setupUi(this);

    obj->id = ID;

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
    ui->departCB->addItem("Общие");



    conn.connOpen();
    QSqlQuery *query = new QSqlQuery();
    query->exec("SELECT  id, Name, Amound FROM Cartriges ORDER BY id");
    while (query->next()) {
            ui->cartrigeCB->addItem(query->value(1).toString(), query->value(0));
    }
    query->exec("SELECT * FROM Printers WHERE ID = '"+QString::number(ID)+"'");
    query->next();
    ui->nameLine->setText(query->value(1).toString());
    int indexDepart = ui->departCB->findText(query->value(2).toString());
    ui->departCB->setCurrentIndex(indexDepart);
    int indexCartrige = ui->cartrigeCB->findData(query->value(3).toString());
    ui->cartrigeCB->setCurrentIndex(indexCartrige);


}

UpdateWindow::~UpdateWindow()
{
    conn.connClose();
    delete ui;
}

void UpdateWindow::UpdateInfo()
{
    if(ui->nameLine->text() == "" || ui->amoundLine->text() == "")
    {
        throw std::runtime_error("Все поля обязательны для заполнения");
    }

    try
    {
        obj->name = ui->nameLine->text();
        obj->depart = ui->departCB->currentText();
        obj->cartrige = ui->cartrigeCB->currentText();
        obj->amound = ui->amoundLine->text().toInt();
        UpdateDB();
    } catch(QException &ex){
        QMessageBox::warning(this, "Исключение", ex.what());
    }

}

void UpdateWindow::UpdateDB()
{
        QSqlQuery *query = new QSqlQuery();
        query->prepare("SELECT ID FROM Cartriges WHERE Name = :n");
        query->bindValue(":n", obj->cartrige);
        query->exec();
        query->next();
        QString idCartrige = query->value(0).toString();
        query->prepare("UPDATE Cartriges SET Name = :n, Amound = '"+QString::number(obj->amound)+"'"
                       "WHERE ID = :i;");
        query->bindValue(":n", obj->cartrige);
        query->bindValue(":i", idCartrige);
        query->exec();
        query->prepare("UPDATE Printers SET Name = :n, Department = :d, Cartrige_ID = :i "
                        "WHERE ID = '"+QString::number(obj->id)+"';");
        query->bindValue(":n", obj->name);
        query->bindValue(":d", obj->depart);
        query->bindValue(":i", idCartrige.toInt());
        query->exec();
}
void UpdateWindow::on_updateButton_clicked()
{
    try
    {
        UpdateInfo();
        this->close();
    }catch(QException &ex){
        QMessageBox::warning(this, "Исключение", ex.what());
    }
}

void UpdateWindow::on_cartrigeCB_currentTextChanged(const QString &arg1)
{
    try
    {
        QSqlQuery *query = new QSqlQuery();
        query->prepare("SELECT Amound FROM Cartriges WHERE Name = :n");
        query->bindValue(":n", arg1);
        query->exec();
        query->next();
        ui->amoundLine->setText(query->value(0).toString());

    } catch(QException &ex){
        QMessageBox::warning(this, "Исключение", ex.what());
    }

}

