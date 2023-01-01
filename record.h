#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDate>
#include <QDateTime>

class Record
{
public:
    Record();

    int getLevel() const;
    void setLevel(int value);

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QString getVersion() const;
    void setVersion(const QString &value);

    QString getJob() const;
    void setJob(const QString &value);

    QDate getDate() const;
    void setDate(const QDate &value);

    QString getEvaluate() const;
    void setEvaluate(const QString &value);

    Record(int _level, QString _name, QString _type, QString _version, QString _job, QString _evaluate);
    Record(int _level, QString _name, QString _type, QString _version, QDate _date, QString _job, QString _evaluate);
    Record(int _level, QString _name, QString _type, QString _version, QString _date, QString _job, QString _evaluate);
private:
    int level;
    QString name, type, version, job;
    QDate date;
    QString evaluate;
};

#endif // RECORD_H
