#include "action.h"
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QStringList>


Action::Action()
{

}

bool Action::do_insert_DB()
{
    QSqlQuery query;
    if(action.toStdString() == "J")
    {
        query.prepare("insert into action (PeerID,JoinTime) values(:peerID,:JoinTime)");
        query.bindValue(0,peer);
        query.bindValue(1,time.toDouble());
        if(!query.exec())
        {
            qDebug() << "Insert J error!";
            return false;
        }
        return true;
    }
    if(action.toStdString() == "G")
    {
        query.prepare("update action set StartTime=:StartTime where peerID = :peerID");
        query.bindValue(0,time.toDouble());
        query.bindValue(1,peer);
        if(!query.exec())
        {
            qDebug() << "Update G error!";
            return false;
        }
        return true;
    }
    if(action.toStdString() == "F")
    {
        query.prepare("update action set FinishTime=:FinishTime where peerID = :peerID");
        query.bindValue(0,time.toDouble());
        query.bindValue(1,peer);
        if(!query.exec())
        {
            qDebug() << "Update F error!";
            return false;
        }
        return true;
    }
    if(action.toStdString() == "L")
    {
        query.prepare("update action set LeaveTime=:LeaveTime where peerID = :peerID");
        query.bindValue(0,time.toDouble());
        query.bindValue(1,peer);
        if(!query.exec())
        {
            qDebug() << "Update L error!";
            return false;
        }
        return true;
    }
    if(action.toStdString() == "SD")
    {
        query.prepare("update action set SumDownload=:SumDownload where peerID = :peerID");
        query.bindValue(0,forthDate.toDouble());
        query.bindValue(1,peer);
        if(!query.exec())
        {
            qDebug() << "Update SD error!";
            return false;
        }
        return true;
    }
    if(action.toStdString() == "SU")
    {
        query.prepare("update action set SumUpload=:SumUpload where peerID = :peerID");
        query.bindValue(0,forthDate.toDouble());
        query.bindValue(1,peer);
        if(!query.exec())
        {
            qDebug() << "Update SU error!";
            return false;
        }
        return true;
    }
    if(action.toStdString() == "A")
    {
        query.prepare("insert into InterArrival (PeerID,ArrivalTime,RcdPiece) values(:peerID,:ArrivalTime,:RcdPiece)");
        query.bindValue(0,peer);
        query.bindValue(1,time.toDouble());
        query.bindValue(2,forthDate.toDouble());
        if(!query.exec())
        {
            qDebug() << "Insert A error!";
            return false;
        }
        return true;
    }
    return false;
}

void Action::do_query_DB()
{
    QSqlQuery query;
    query.exec("select * from action where JoinTime <> '' and StartTime <> '' and FinishTime <> '' and LeaveTime <> ''");
    //    query.exec("select * from action");


    while(query.next())
    {
        qDebug() << query.value(1).toString() << query.value(2).toDouble()
                <<query.value(3).toDouble()<<query.value(4).toDouble()<<query.value(5).toDouble();
    }

    qDebug() << "Total:"<<totalRecordNum();
    qDebug() <<"Effective:"<<effectiveRecordNum();
    qDebug() <<"Ineffective:"<<ineffectiveRecordNum();
    qDebug() <<"Avg:"<<avgDownloadTime();
}

int Action::totalRecordNum()
{
    QSqlQuery query;
    query.exec("select count(*) from action");
    query.next();
    return query.value(0).toInt();
}

int Action::effectiveRecordNum()
{
    QSqlQuery query;
    query.exec("select count(*) from action where JoinTime <> 0 and StartTime <> 0 and FinishTime <> 0 and LeaveTime <> 0");
    query.next();
    return query.value(0).toInt();
}

int Action::ineffectiveRecordNum()
{
    QSqlQuery query;
    query.exec("select count(*) from action where JoinTime = 0 or StartTime = 0 or FinishTime = 0 or LeaveTime <> 0");
    query.next();
    return query.value(0).toInt();
}

double Action::avgDownloadTime()
{
    QSqlQuery query;
    query.exec("select avg(result) from (select (FinishTime-StartTime) as result from action where JoinTime <> 0 and StartTime <> 0 and FinishTime <> 0 and LeaveTime <> 0)");
    query.next();
    return query.value(0).toDouble();
}

void Action::setDate(QString str)
{
    QStringList list = str.split(" ");
    action = list.value(0);
    time = list.value(1);
    peer = list.value(2);
    forthDate = list.value(3);
}
