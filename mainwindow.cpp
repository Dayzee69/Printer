#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->tableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    ReadDB();
    ui->tableWidget->setSortingEnabled(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadDB()
{
    DBConnect conn;
    conn.connOpen();

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    QStringList headers = {"№","Наименование","Отдел","Картридж","Количество"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setShowGrid(true);
    QSqlQuery query("SELECT  Printers.ID, Printers.Name, Printers.Department, Cartriges.Name, Cartriges.Amound FROM Printers, Cartriges "
                    "WHERE Printers.Cartrige_ID = Cartriges.ID "
                    "ORDER BY Printers.ID"
                    );
    for(int i = 0; query.next(); i++)
    {
            ui->tableWidget->insertRow(i);
        for (int j = 0 ; j< 5; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(j).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,j, item);
        }
    }
    conn.connClose();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
}

void MainWindow::ReadDBup()
{
    DBConnect conn;
    conn.connOpen();

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    QStringList headers = {"№","Наименование","Отдел","Картридж","Количество"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setShowGrid(true);
    QSqlQuery query("SELECT  Printers.ID, Printers.Name, Printers.Department, Cartriges.Name, Cartriges.Amound FROM Printers, Cartriges "
                    "WHERE Printers.Cartrige_ID = Cartriges.ID "
                    "ORDER BY Printers.ID"
                    );
    for(int i = 0; query.next(); i++)
    {
        for (int j = 0 ; j< 5; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(j).toString());
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,j, item);
        }
    }
    conn.connClose();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
}

void MainWindow::ReadDBadd()
{
    DBConnect conn;
    conn.connOpen();

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    QStringList headers = {"№","Наименование","Отдел","Картридж","Количество"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setShowGrid(true);


    QSqlQuery *query_check = new QSqlQuery();
           query_check->prepare("SELECT COUNT(*) FROM Printers");

    query_check->exec();
    query_check->next();
    int check = query_check->value(0).toInt();

   if(check > ui->tableWidget->rowCount())
   {
       QSqlQuery query("SELECT  Printers.ID, Printers.Name, Printers.Department, Cartriges.Name, Cartriges.Amound FROM Printers, Cartriges "
                       "WHERE Printers.Cartrige_ID = Cartriges.ID "
                       "ORDER BY Printers.ID"
                       );
       ui->tableWidget->insertRow(1);
       for(int i = 0; query.next(); i++)
       {
           for (int j = 0 ; j< 5; j++)
           {
               QTableWidgetItem *item = new QTableWidgetItem(query.value(j).toString());
               item->setFlags(item->flags() ^ Qt::ItemIsEditable);
               ui->tableWidget->setItem(i,j, item);
           }
       }

   }

     ui->tableWidget->resizeColumnsToContents();
         ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    conn.connClose();

}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    QAction * editUpdate = new QAction("Изменить", this);
    connect(editUpdate, SIGNAL(triggered()), this, SLOT(slotUptade()));
    menu->addAction(editUpdate);
    if(ui->tableWidget->selectionModel()->currentIndex().row() >= 0){
        menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::slotUptade()
{

    QModelIndex index = ui->tableWidget->currentIndex();
    int setRow = index.row();
    QVariant obj = ui->tableWidget->model()->data(index.sibling(setRow,0));
    int Id = obj.toInt();
    try{
        UpdateWindow *upWin = new UpdateWindow(Id);
        upWin->setAttribute(Qt::WA_DeleteOnClose);
        connect(upWin, &UpdateWindow::destroyed, this, &MainWindow::ReadDBup);
        upWin->show();
    }catch(QException &ex){
        QMessageBox::warning(this, "Исключение", ex.what());
    }

}

void MainWindow::on_action_2_triggered()
{
    try{
        AddWindow *addWin = new AddWindow();
        addWin->show();
    }catch(QException &ex){
        QMessageBox::warning(this, "Исключение", ex.what());
    }
}

void MainWindow::on_action_3_triggered()
{
    try{
    AddPrinterWindow *addPrinterWin = new AddPrinterWindow();
    addPrinterWin->setAttribute(Qt::WA_DeleteOnClose);
    connect(addPrinterWin, &AddPrinterWindow::destroyed, this, &MainWindow::ReadDBadd);
    addPrinterWin->show();
    }catch(QException ex){
        QMessageBox::warning(this, "Исключение", ex.what());
    }
}

