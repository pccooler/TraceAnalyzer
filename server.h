#ifndef SERVER_H
#define SERVER_H

#include <QString>

class Server
{
public:
    Server();
    void setDate(const QString str);
    bool do_insert_DB();//�������ݵ�DB

private:
    QString serverID;
    QString type;
    QString rate;
};

#endif // SERVER_H
