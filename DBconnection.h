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
    return true;
}

static bool create_Table()
{
    QSqlQuery query;


    //建立SimSce表
    if(!query.exec("create table SimSce ("
                   "peerID varchar(20) Primary Key,"
                   "JoinTime double,"
                   "StartTime double,"
                   "FinishTime double,"
                   "LeaveTime double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create SimSce Table."),
                              QMessageBox::Cancel);
        return false;
    }

    //建立Out表
    /*
    <time> <from> <to> <bytes> <pkts> <pArrivals> <pDepartures> <pDrops> <bArrivals> <bDepartures> <bDrops>
    (1)time：时间(s)
    (2)fromIP：该链路起始端节点IP
    (3)toIP：该链路末端节点IP
    (4)bytes：该链路在此单位时间间隔内传输的字节数(bytes)
    (5)pkts：该链路在此单位时间间隔内传输的数据包数量(packets)
    (6)pArrivals：收到的数据包数量(packets)
    (7)pDepartures：离开的数据包数量(packets)
    (8)pDrops：丢失的数据包数量(packets)
    (9)bArrivals：收到的字节数(bytes)
    (10)bDepartures：离开的字节数(bytes)
    (11)bDrops：丢失的字节数(bytes)
    */
    if(!query.exec("create table Out ("
                   "time double,"
                   "fromIP double,"
                   "toIP double,"
                   "bytes double,"
                   "pkts double,"
                   "pArrivals double,"
                   "pDepartures double,"
                   "pDrops double,"
                   "bArrivals double,"
                   "bDepartures double,"
                   "bDrops double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create Out Table."),
                              QMessageBox::Cancel);
        return false;
    }

    //建立Server表
    if(!query.exec("create table Server ("
                   "peerID varchar(20) Primary Key,"
                   "JoinTime double,"
                   "StartTime double,"
                   "FinishTime double,"
                   "LeaveTime double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create Server Table."),
                              QMessageBox::Cancel);
        return false;
    }


    //建立Action表
    if(!query.exec("create table Action ("
                   "peerID varchar(20) Primary Key,"
                   "JoinTime double,"
                   "StartTime double,"
                   "FinishTime double,"
                   "LeaveTime double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create Action Table."),
                              QMessageBox::Cancel);
        return false;
    }

    return true;
}


#endif // DBCONNECTION_H
