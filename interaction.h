#ifndef INTERACTION_H
#define INTERACTION_H
#include <QString>

class InterAction
{
public:
    InterAction();
    void setDate(const QString str);
    bool do_insert_DB();//插入数据到DB


private:
    QString type;
    QString time;
    QString peerID;
    QString pieceArrivedSequence;
};

#endif // INTERACTION_H
