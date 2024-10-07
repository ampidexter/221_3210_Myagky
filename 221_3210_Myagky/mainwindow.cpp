#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Сумма" << "Кошелек" << "Дата" << "Хеш");

    QString homeDir = QDir::homePath() + "/221_3210_Myagky";
    loadTransactions(homeDir + "/transactions.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTransactions(const QString& fileName)
{
    QFile file(fileName);

    if (!file.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл не найден: " + fileName);
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + fileName);
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList transaction = line.split(" ");

        if (transaction.size() == 4) {
            int rowCount = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);
            for (int i = 0; i < transaction.size(); ++i) {
                ui->tableWidget->setItem(rowCount, i, new QTableWidgetItem(transaction[i]));
            }
        }
    }

    file.close();
}
