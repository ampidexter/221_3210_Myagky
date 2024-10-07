#ifndef ADDTRANSACTIONDIALOG_H
#define ADDTRANSACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class AddTransactionDialog;
}

class AddTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTransactionDialog(QWidget *parent = nullptr);
    ~AddTransactionDialog();

signals:
    void transactionAdded(const QString &amount, const QString &wallet, const QString &date, const QString &hash);

private slots:
    void on_saveButton_clicked();

private:
    Ui::AddTransactionDialog *ui;
    bool isInputValid(const QString &amount, const QString &wallet, const QString &date);
    QString calculateHash(const QString &amount, const QString &wallet, const QString &date, const QString &previousHash);
    QString getLastTransactionHash();
    void saveTransaction(const QString &amount, const QString &wallet, const QString &date, const QString &hash);
};

#endif // ADDTRANSACTIONDIALOG_H
