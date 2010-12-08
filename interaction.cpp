#include "interaction.h"
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

InterAction::InterAction()
{
}

void InterAction::setDate(const QString str)
{
    QStringList strList = str.trimmed().split(" ");
    type = strList.value(0);
    time = strList.value(1);
    peerID = strList.value(2);
    pieceArrivedSequence = strList.value(3);
}

bool InterAction::do_insert_DB()
{
    QSqlQuery query;

    query.prepare("insert into InterAction (type,time,peerID,pieceArrivedSequence) values(:type,:time,:peerID,:pieceArrivedSequence)");
    query.bindValue(0,type);
    query.bindValue(1,time.toDouble());
    query.bindValue(2,peerID);
    query.bindValue(3,pieceArrivedSequence);

    if(!query.exec())
    {
        qDebug() << "Insert InterAction error!";
        return false;
    }
    return true;
}
