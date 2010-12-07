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
    //peerID���ϴ��������ش���
    if(!query.exec("create table SimSce ("
                   "NodeType varchar(1),"
                   "peerID varchar(20) primary key,"
                   "Upload double,"
                   "Download double)"))
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
    //������ID�����������͡������������
    if(!query.exec("create table Server ("
                   "ServerID varchar(20),"
                   "Type varchar(1),"
                   "Rate double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create Server Table."),
                              QMessageBox::Cancel);
        return false;
    }


    //����Action��
    //ActionType('N':��ͨ;'A':inter-arrival;'C':interestConct)��peerID��
    //����ʱ�䡢��ʼʱ�䡢���ʱ�䡢�뿪ʱ�䡢�����ܿ������ϴ��ܿ���
    if(!query.exec("create table Action ("
                   "peerID varchar(20) primary key,"
                   "JoinTime double,"
                   "StartTime double,"
                   "FinishTime double,"
                   "LeaveTime double,"
                   "SumDownload double,"
                   "SumUpload double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create Action Table."),
                              QMessageBox::Cancel);
        return false;
    }

    //����InterArrival��
    //ActionType,PeerID,ArrivalTime,RcdPiece
    if(!query.exec("create table InterArrival ("
                   "peerID varchar(20),"
                   "ArrivalTime double,"
                   "RcdPiece double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create InterArrival Table."),
                              QMessageBox::Cancel);
        return false;
    }

    //����InterestConct��
    //ActionType,Time,InterestConctNum
    if(!query.exec("create table InterestConct ("
                   "Time double,"
                   "InterestConctNum double)"))
    {
        QMessageBox::critical(0, qApp->tr("Cannot Create Table"),
                              qApp->tr("Unable to Create InterestConct Table."),
                              QMessageBox::Cancel);
        return false;
    }

    return true;
}


#endif // DBCONNECTION_H
