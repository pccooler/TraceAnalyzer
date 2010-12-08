#include "server.h"
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QDebug>

Server::Server()
{
}

void Server::setDate(const QString str)
{
    QStringList strList = str.trimmed().split(" ");
    serverID = strList.value(1);
    type = strList.value(2);
    rate = strList.value(5);
    time = strList.value(0);
    interestConnectNum = strList.value(4);
}

bool Server::do_insert_DB()
{
    QSqlQuery query;
    if(type.toStdString() == "S")
    {
        query.prepare("insert into server (serverID,Type,Rate,Time) values(:serverID,:Type,:Rate,:Time)");
        query.bindValue(0,serverID);
        query.bindValue(1,type);
        query.bindValue(2,rate.toDouble());
        query.bindValue(3,time.toDouble());

        if(!query.exec())
        {
            qDebug() << "Insert S error!";
            return false;
        }
        return true;
    }
    if(type.toStdString() == "P")
    {
        double sum = 0;
        query.prepare("select InterestConctNum from InterestConct where Time = :Time");
        query.bindValue(0,time.toDouble());
        query.exec();
        if(query.next())  sum = query.value(0).toDouble();
        else
        {
            query.prepare("insert into InterestConct (Time,InterestConctNum) values(:Time,:InterestConctNum)");
            query.bindValue(0,time.toDouble());
            query.bindValue(1,interestConnectNum.toDouble());
            if(!query.exec())
            {
                qDebug() << "Insert P error!";
                return false;
            }
            return true;
        }

        sum += time.toDouble();
        query.prepare("Update InterestConct set InterestConctNum = :InterestConctNum where Time = :Time");
        query.bindValue(1,time.toDouble());
        query.bindValue(0,interestConnectNum.toDouble());
        if(!query.exec())
        {
            qDebug() << "Insert P error!";
            return false;
        }

        return true;
    }
}
