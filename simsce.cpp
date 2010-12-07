#include "simsce.h"
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QStringList>

SimSce::SimSce()
{
}

bool SimSce::do_insert_DB()
{
    QSqlQuery query;
    if(nodeType.toStdString() == "P")
    {
        query.prepare("insert into Simsce (NodeType,peerID,Download,Upload) values(:NodeType,:peerID,:Download,:Upload)");
        query.bindValue(0,nodeType);
        query.bindValue(1,peerID);
        query.bindValue(2,downBandWidth.toDouble());
        query.bindValue(3,upBandWidth.toDouble());
        if(!query.exec())
        {
            qDebug() << "Insert P error!";
            return false;
        }
        return true;
    }
    return false;
}

void SimSce::setDate(QString str)
{
    QStringList strList = str.split(" ");
    nodeType = strList.value(2);
    peerID = strList.value(1);
    downBandWidth = strList.value(4);
    upBandWidth = strList.value(5);
    downBandWidth = downBandWidth.replace(";","");
    upBandWidth = upBandWidth.replace(";","");
    downBandWidth = downBandWidth.mid(downBandWidth.indexOf(":")+1);
    upBandWidth = upBandWidth.mid(upBandWidth.indexOf(":")+1);
}
