#ifndef ACTION_H
#define ACTION_H
#include <QTextStream>

class Action
{
public:
    Action();

    void setDate(QString str);//���ó�Աֵ
    bool do_insert_DB();//�������ݵ�DB
    void do_query_DB();//��ѯDB
    int totalRecordNum();
    int effectiveRecordNum();
    int ineffectiveRecordNum();
    double avgDownloadTime();

private:
    QString action;//peer����Ϊ
    QString time;//���¼�����ʱ��
    QString peer;//peer ID
    QString forthDate;//�����ֶ�
};

#endif // ACTION_H
