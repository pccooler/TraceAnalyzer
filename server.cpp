#include "server.h"
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QDebug>

Server::Server()
{
    uniID = 1;
}

void Server::setDate(const QString str)
{
    QStringList strList = str.split(" ");
    serverID = strList.value(0);
    type = strList.value(1);
    rate = strList.value(4);
}

bool Server::do_insert_DB()
{
    QSqlQuery query;
    if(type.toStdString() == "S")
    {
        query.prepare("insert into server (serverID,Type,Rate,uniID) values(:serverID,:Type,:Rate,:uniID)");
        query.bindValue(0,serverID);
        query.bindValue(1,type);
        query.bindValue(2,rate.toDouble());
        query.bindValue(3,uniID);

        if(!query.exec())
        {
            qDebug() << "Insert S error!";
            return false;
        }
        ++uniID;
        return true;
    }
}
