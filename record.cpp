#include "record.h"

Record::Record():
    level(-1), name("defaultName"), type("defaultType"),
    version("defaultVersion"), job("defaultJob"),
    evaluate("defaultEvaluate")
{
    date = QDate::currentDate();
}

Record::Record(int _level, QString _name, QString _type,
               QString _version, QString _job, QString _evaluate):
    level(_level), name(_name), type(_type),
    version(_version), job(_job),
    evaluate(_evaluate)
{
    date = QDate::currentDate();
}

Record::Record(int _level, QString _name, QString _type,
               QString _version, QDate _date, QString _job, QString _evaluate):
    level(_level), name(_name), type(_type),
    version(_version), job(_job), date(_date),
    evaluate(_evaluate){}

Record::Record(int _level, QString _name, QString _type,
               QString _version, QString _date, QString _job, QString _evaluate):
    level(_level), name(_name), type(_type),
    version(_version), job(_job),
    evaluate(_evaluate)
{
    date = QDate::fromString(_date, "yyyy-MM-dd");
}

int Record::getLevel() const
{
    return level;
}

void Record::setLevel(int value)
{
    level = value;
}

QString Record::getName() const
{
    return name;
}

void Record::setName(const QString &value)
{
    name = value;
}

QString Record::getType() const
{
    return type;
}

void Record::setType(const QString &value)
{
    type = value;
}

QString Record::getVersion() const
{
    return version;
}

void Record::setVersion(const QString &value)
{
    version = value;
}

QString Record::getJob() const
{
    return job;
}

void Record::setJob(const QString &value)
{
    job = value;
}

QDate Record::getDate() const
{
    return date;
}

void Record::setDate(const QDate &value)
{
    date = value;
}

QString Record::getEvaluate() const
{
    return evaluate;
}

void Record::setEvaluate(const QString &value)
{
    evaluate = value;
}
