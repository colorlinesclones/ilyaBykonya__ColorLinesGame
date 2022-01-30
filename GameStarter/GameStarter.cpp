#include "GameStarter.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QFile>
#include <QSet>
#include <QFileInfo>
#include <QDebug>

bool GameStarter::makeValidConfiguration()
{
    if(makeSqliteFile() == false) return false;
    if(makeDatabaseConnection() == false) return false;
    if(makeTableConfiguration() == false) return false;
    if(makeTableData() == false) return false;
    return true;
}
bool GameStarter::makeSqliteFile()
{
    if(QFile::exists("ColorLines.sqlite") == false) {
        return QFile{ "ColorLines.sqlite" }.open(QIODevice::OpenModeFlag::ReadWrite);
    }

    return true;
}
bool GameStarter::makeDatabaseConnection()
{
    //Открываем соединение
    auto database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("ColorLines.sqlite");
    return database.open();
}
bool GameStarter::makeTableConfiguration()
{
    //Создаём таблицу, если её нет
    QSqlQuery query{ QString("select name from sqlite_master where type='table' AND name='GameState';") };
    if(query.next()) return true;

    return query.exec("create table GameState ("
                      "key STRING UNIQUE NOT NULL,"
                      "value INTEGER);");
}
bool GameStarter::makeTableData()
{
    //Задаём поля строки таблицы
    QSqlQuery query("select key from GameState;");
    QSet<QString> allKeys;
    while (query.next()) { allKeys.insert(query.value(0).toString()); }

    //Поле счёта в игре:
    if(allKeys.contains("score") == false)
        if(query.exec("insert into GameState('key') values('score');") == false)
            return false;

    for(int row = 0; row < 9; ++row) {
        for(int column = 0; column < 9; ++column) {
            QString requiredKey = QString("%1_%2").arg(row).arg(column);
            if(allKeys.contains(requiredKey) == false)
                if(query.exec(QString("insert into GameState('key') values('%1');").arg(requiredKey)) == false)
                    return false;
        }
    }

    return true;
}
