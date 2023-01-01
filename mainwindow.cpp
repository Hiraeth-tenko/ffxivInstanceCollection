#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddlg.h"
#include "record.h"


QSqlTableModel* tableModel;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Allegdb = QSqlDatabase::addDatabase("QSQLITE", "mainWindow");
    Allegdb.setDatabaseName("AllegDatabase.db");
    if(!Allegdb.open()){
        qDebug() << "Database error: " << Allegdb.lastError().text();
    }

    tableModel = new QSqlTableModel(this);
    tableModel->setTable("records");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->select();
    QTableView* qtv = ui->manager->findChild<QTableView*>("tableView");
    if(qtv){
        qtv->setModel(tableModel);
        qtv->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_showAllBtn_clicked()
{
    tableModel->clear();
    tableModel->setTable("records");
    tableModel->select();
    QTableView* qtv = ui->manager->findChild<QTableView*>("tableView");
    if(qtv){
        qtv->setModel(tableModel);
        qtv->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    }
}

void MainWindow::on_addBtn_clicked()
{
    addDlg *dlg = new addDlg();
    connect(dlg,SIGNAL(dlgReturn(Record)),this, SLOT(getAddRecord(Record)));
    dlg->show();
}

void MainWindow::getAddRecord(Record record)
{
    QSqlQuery query(Allegdb);
    query.clear();
    query.prepare("insert into records(level, name, type, version, date, job, evaluate) "
                  "values(:level, :name, :type, :version, :date, :job, :evaluate)");
    query.bindValue(":level", record.getLevel());
    query.bindValue(":name", record.getName());
    query.bindValue(":type", record.getType());
    query.bindValue(":version", record.getVersion());
    query.bindValue(":date", record.getDate().toString("yyyy-MM-dd"));
    query.bindValue(":job",record.getJob());
    query.bindValue(":evaluate", record.getEvaluate());
    if(!query.exec()){
        qDebug() << query.lastError().text();
    }
    query.finish();
    on_showAllBtn_clicked();
}

void MainWindow::on_searchBtn_clicked()
{
    QLineEdit* nameLE = ui->nameLE;
    QComboBox* typeCB = ui->typeCB;
    QComboBox* jobCB = ui->jobCB;
    QComboBox* versionCB = ui->versionCB;
    QString name = nameLE->text();
    QString type = typeCB->currentText();
    QString version = versionCB->currentText();
    QString job = jobCB->currentText();
    QString sql = "";
    int cnt = 0;
    if(type != "无"){
        sql += (cnt ? " and ":"");
        sql += "type = '" + type + "'";
        if(cnt == 0)cnt = 1;
    }
    if(job != "无"){
        sql += (cnt ? " and ":"");
        sql += "job = '" + job + "'";
        if(cnt == 0)cnt = 1;
    }
    if(version != "无"){
        sql += (cnt ? " and ":"");
        sql += "version = '" + version + "'";
        if(cnt == 0)cnt = 1;
    }
    if(name != ""){
        sql += (cnt ? " and ":"");
        sql += "name like '%" + name + "%'";
    }
    qDebug() << sql;
    tableModel->setFilter(sql);
    tableModel->select();
}

void MainWindow::on_deleteBtn_clicked()
{
    int curRow = ui->tableView->currentIndex().row();

    tableModel->removeRow(curRow);
    QMessageBox::warning(this, tr("delete current row"),
                                  tr("sure?"),
                                  QMessageBox::Yes,
                                  QMessageBox::No);
}

void MainWindow::on_submitBtn_clicked()
{
    tableModel->database().transaction();
    if(tableModel->submitAll()){
        tableModel->database().commit();
    }
    else{
        tableModel->database().rollback();
        QMessageBox::warning(this, tr("tableModel"),
                             tr("tableModel error: %1").arg(tableModel->lastError().text()));
    }
}

void MainWindow::on_revertBtn_clicked()
{
    tableModel->revertAll();
}
