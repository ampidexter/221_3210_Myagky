#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addTransaction_clicked();
    void onTransactionAdded(const QString& amount, const QString& wallet, const QString& date, const QString& hash); // новый слот для обработки добавления транзакции

private:
    Ui::MainWindow *ui;

    void loadTransactions(const QString& fileName);
};

#endif // MAINWINDOW_H
