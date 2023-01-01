#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("AllegDatabase.db");
    if(!db.open()){
        qDebug() << "Database error: " << db.lastError();
    }
    else{
        QSqlQuery query(db);
        query.exec(QString("create table records(id integer primary key autoincrement, "
                              "level int, name text, type text, version text, "
                              "date text, job text, evaluate text)"));
        query.finish();
    }
    db.close();
    MainWindow w;
    w.show();
    return a.exec();
}
