#include "addtransactiondialog.h"
#include "ui_addtransactiondialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QDir>
#include <QRegularExpression>

AddTransactionDialog::AddTransactionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTransactionDialog)
{
    ui->setupUi(this);
}

AddTransactionDialog::~AddTransactionDialog()
{
    delete ui;
}

bool AddTransactionDialog::isInputValid(const QString& amount, const QString& wallet, const QString& date) {
    QRegularExpression amountRegExp("^\\d{7}$");
    QRegularExpression walletRegExp("^\\d{6}$");
    QRegularExpression dateRegExp("^\\d{4}\\.\\d{2}\\.\\d{2}_\\d{2}:\\d{2}:\\d{2}$");

    return amountRegExp.match(amount).hasMatch() &&
           walletRegExp.match(wallet).hasMatch() &&
           dateRegExp.match(date).hasMatch();
}

QString AddTransactionDialog::calculateHash(const QString& amount, const QString& wallet, const QString& date, const QString& previousHash) {
    QString hashInput = amount + wallet + date + previousHash;
    QByteArray hash = QCryptographicHash::hash(hashInput.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

QString AddTransactionDialog::getLastTransactionHash() {
    QString fileName = QDir::homePath() + "/221_3210_Myagky/transactions.txt";
    QFile file(fileName);

    if (!file.exists()) {
        return "0000000000000000000000000000000000000000000000000000000000000000";
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "0000000000000000000000000000000000000000000000000000000000000000";
    }

    QTextStream in(&file);
    QString lastLine;

    while (!in.atEnd()) {
        lastLine = in.readLine();
    }

    file.close();

    if (lastLine.isEmpty()) {
        return "0000000000000000000000000000000000000000000000000000000000000000";
    }

    QStringList transactionData = lastLine.split(" ");

    if (transactionData.size() == 4) {
        return transactionData.at(3);
    }

    return "0000000000000000000000000000000000000000000000000000000000000000";
}

void AddTransactionDialog::on_saveButton_clicked()
{
    QString amount = ui->amountLineEdit->text();
    QString wallet = ui->walletLineEdit->text();
    QString date = ui->dateLineEdit->text();

    if (!isInputValid(amount, wallet, date)) {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные! Проверьте формат суммы, кошелька и даты.");
        return;
    }

    QString previousHash = getLastTransactionHash();
    QString hash = calculateHash(amount, wallet, date, previousHash);

    saveTransaction(amount, wallet, date, hash);

    emit transactionAdded(amount, wallet, date, hash);

    accept();
}

void AddTransactionDialog::saveTransaction(const QString& amount, const QString& wallet, const QString& date, const QString& hash) {
    QString fileName = QDir::homePath() + "/221_3210_Myagky/transactions.txt";
    QFile file(fileName);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << amount << " " << wallet << " " << date << " " << hash << "\n";
        file.close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
    }
}
