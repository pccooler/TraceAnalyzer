#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

static QSqlDatabase db;

static bool connect_DB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
                              qApp->tr("Unable to establish a database connection."),
                              QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("create table Action ("
               "peerID varchar(20) Primary Key,"
               "JoinTime double,"
               "StartTime double,"
               "FinishTime double,"
               "LeaveTime double)");
    return true;
}


#endif // DBCONNECTION_H
