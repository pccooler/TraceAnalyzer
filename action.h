#ifndef ACTION_H
#define ACTION_H
#include <QTextStream>

class Action
{
public:
    Action();

    void setAction(QString str);//设置成员action值
    void setTime(QString str);//设置成员time值
    void setPeer(QString str);//设置成员peer值
    void setDate(QString str);//设置成员值
    bool do_insert_DB();//插入数据到DB
    void do_query_DB();//查询DB
    int totalRecordNum();
    int effectiveRecordNum();
    int ineffectiveRecordNum();
    double avgDownloadTime();

private:
    QString action;//peer的行为
    QString time;//本事件发生时刻
    QString peer;//peer ID



};

#endif // ACTION_H
