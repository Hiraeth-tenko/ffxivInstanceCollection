#include "adddlg.h"
#include "ui_adddlg.h"


addDlg::addDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDlg)
{
    ui->setupUi(this);

    ffxivdb = QSqlDatabase::addDatabase("QSQLITE", "ffxiv");
    ffxivdb.setDatabaseName("ffxiv.db");
    if(!ffxivdb.open()){
        qDebug() << "ffxiv.db open error: " << ffxivdb.lastError();
    }
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
}

addDlg::~addDlg()
{
    delete ui;
    ffxivdb.close();
}

void addDlg::on_buttonBox_accepted()
{
    int level = ui->levelLE->text().toInt();
    QString name = ui->nameCB->currentText(),
            type = ui->typeLE->text(),
            version = ui->versionLE->text(),
            job = ui->jobCB->currentText(),
            date = ui->dateEdit->text(),
            evaluate = ui->evaluateCB->currentText();
    Record record(level, name, type, version, date, job , evaluate);
    emit dlgReturn(record);
}

void addDlg::on_levelLE_editingFinished()
{
    QLineEdit* levelLE = ui->levelLE;
    QComboBox* nameCB = ui->nameCB;

    QString qstr = levelLE->text();
    int level = qstr.toInt();
    qDebug() << level;

    QSqlQuery query(ffxivdb);
    query.prepare("select * from ffxiv where level = ?");
    query.addBindValue(level);
    query.exec();

    nameCB->clear();
    while(query.next()){
        QString name = query.value(2).toString();
        nameCB->addItem(name);
    }
    query.finish();
}

void addDlg::on_nameCB_currentTextChanged(const QString &arg1)
{
    QLineEdit* typeLE = ui->typeLE;
    QLineEdit* versionLE = ui->versionLE;

    QSqlQuery query(ffxivdb);
    query.prepare("select * from ffxiv where name = ?");
    query.addBindValue(arg1);
    query.exec();
    query.first();
    typeLE->setText(query.value(3).toString());
    versionLE->setText(query.value(4).toString());
    query.finish();
}
