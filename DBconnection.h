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


    //����SimSce��
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

    //����Out��
    /*
    <time> <from> <to> <bytes> <pkts> <pArrivals> <pDepartures> <pDrops> <bArrivals> <bDepartures> <bDrops>
    (1)time��ʱ��(s)
    (2)fromIP������·��ʼ�˽ڵ�IP
    (3)toIP������·ĩ�˽ڵ�IP
    (4)bytes������·�ڴ˵�λʱ�����ڴ�����ֽ���(bytes)
    (5)pkts������·�ڴ˵�λʱ�����ڴ�������ݰ�����(packets)
    (6)pArrivals���յ������ݰ�����(packets)
    (7)pDepartures���뿪�����ݰ�����(packets)
    (8)pDrops����ʧ�����ݰ�����(packets)
    (9)bArrivals���յ����ֽ���(bytes)
    (10)bDepartures���뿪���ֽ���(bytes)
    (11)bDrops����ʧ���ֽ���(bytes)
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

    //����Server��
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


    //����Action��
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
