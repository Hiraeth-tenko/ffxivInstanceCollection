#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QTableView>
#include <QMessageBox>
#include "record.h"

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

    void on_showAllBtn_clicked();

    void on_addBtn_clicked();

    void on_searchBtn_clicked();

    void on_deleteBtn_clicked();

    void on_submitBtn_clicked();

    void on_revertBtn_clicked();

    void getAddRecord(Record record);

private:
    Ui::MainWindow *ui;
    QSqlDatabase Allegdb;
};
#endif // MAINWINDOW_H
