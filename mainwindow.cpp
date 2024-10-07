#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Сумма" << "Кошелек" << "Дата" << "Хеш");

    QStringList transaction1;
    transaction1 << "0057600" << "112233" << "2024.06.15_12:00:00" << "a66...ae3";

    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    for (int i = 0; i < transaction1.size(); ++i) {
        ui->tableWidget->setItem(rowCount, i, new QTableWidgetItem(transaction1[i]));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
