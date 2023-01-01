#ifndef ADDDLG_H
#define ADDDLG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "record.h"

namespace Ui {
class addDlg;
}

class addDlg : public QDialog
{
    Q_OBJECT

public:
    explicit addDlg(QWidget *parent = nullptr);
    ~addDlg();

private slots:
    void on_buttonBox_accepted();

    void on_levelLE_editingFinished();

    void on_nameCB_currentTextChanged(const QString &arg1);

private:
    Ui::addDlg *ui;
    QSqlDatabase ffxivdb;

signals:
    void dlgReturn(Record record);
};

#endif // ADDDLG_H
