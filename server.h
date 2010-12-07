#ifndef SERVER_H
#define SERVER_H

#include <QString>

class Server
{
public:
    Server();
    void setDate(const QString str);
    bool do_insert_DB();//插入数据到DB

private:
    QString serverID;
    QString type;
    QString rate;
};

#endif // SERVER_H
