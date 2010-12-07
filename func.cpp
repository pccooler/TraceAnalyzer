#include "func.h"
#include "simsce.h"
#include "out.h"
#include "server.h"
#include "action.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QRegExp>
#include <QTextCodec>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>

func::func()
{
}

bool func::do_load_file(QStringList fileNames)
{
    foreach(QString fileName,fileNames)
        //处理打开多个文件
    {
        if(!fileName.isEmpty())
        {
            QFile file(fileName);
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                return false;
            }

            QTextStream in(&file);
            QString line;

            if(fileName.contains(QRegExp(".*/out.*.0")))//正则表达式匹配out?.0文件
            {
                line = in.readLine();
                while(!line.isNull())
                {
                    if(line.contains(QRegExp("Cost .* seconds totally.")))
                    {
                        QStringList lineList = line.split(" ");
                        line = lineList.value(1);
                        qDebug()<<line;
                    }
                    line = in.readLine();
                }

            }
            if(fileName.contains(QRegExp(".*/[Ss]im[Ss]ce.*")))//正则表达式匹配SimSce文件
            {
                SimSce *simsce_p = new SimSce();
                line = in.readLine();
                while(!line.isNull())
                {
                    if(line.contains("[Sessions]"))
                    {
                        line = in.readLine();
                        QStringList numlist = line.split(",");
                        //获取文件块数
                        QString num = numlist.value(0);
                        num = num.mid(line.indexOf("(")+1);
                        filePieceNum = num.toInt();
                        //获取seed上传带宽
                        num = numlist.value(3);
                        numlist = num.split(")");
                        num = numlist.value(0);
                        seedUpLink = num.toDouble();

                        qDebug()<<filePieceNum<<seedUpLink;
                    }
                    if(line.contains("[Nodes]"))
                    {
                        line = in.readLine();
                        while(!line.contains("[Network]"))
                        {
                            simsce_p->setDate(line);
                            simsce_p->do_insert_DB();
                            line = in.readLine();
                        }
                    }
                    line = in.readLine();
                }

            }
            if(fileName.contains(QRegExp(".*/[Oo]ut.*")))//正则表达式匹配out文件
            {

            }
            if(fileName.contains(QRegExp(".*/[Ss]erver.*")))//正则表达式匹配server文件
            {
                Server *server_p = new Server();
                line = in.readLine();
                while(!line.isNull())
                {
                    server_p->setDate(line);
                    server_p->do_insert_DB();
                    line = in.readLine();
                }
            }
            if(fileName.contains(QRegExp(".*/[Aa]ction.*")))//正则表达式匹配action文件
            {
                Action *action_p = new Action();

                line = in.readLine();
                while(!line.isNull())
                {
                    action_p->setDate(line);
                    action_p->do_insert_DB();
                    line = in.readLine();
                }

                delete action_p;
                action_p = NULL;
            }
        }
    }
    return true;
}

bool func::saveFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
        //以只写方式打开文件，如果打开失败则弹出提示框并返回
    {
        return false;
    }
    QTextStream out(&file);
    return true;
}

double func::avg_peer_download_time()//平均节点下载时间
{
    QSqlQuery query;
    if(!query.exec("create view tempview as "
               "select (FinishTime-JoinTime) as DownTime from action "
               "where JoinTime <> 0 and StartTime <> 0 "
               "and FinishTime <> 0 and LeaveTime <> 0"))
        qDebug()<<"error create tempview";
    if(!query.exec("select count(*) from tempview"))
        qDebug()<<"error select tempview";
    query.next();
    double sumPeers = query.value(0).toDouble();
    if(!query.exec("select sum(DownTime) from tempview"))
        qDebug()<<"error select sum in tempview";
    query.next();
    double sumTime = query.value(0).toDouble();
    if(!query.exec("drop view tempview"))
        qDebug()<<"error drop tempview";
    return sumTime/sumPeers;
}

double func::avg_seed_uplink_utilization()//平均种子带宽利用率
{
    QSqlQuery query;
    if(!query.exec("select sum(Rate) from Server where Type = 'S'"))
        qDebug()<<"error select sum(Rate) from Server";
    query.next();
    double sumRate = query.value(0).toDouble();
    if(!query.exec("select count(*) from Server where Type = 'S'"))
        qDebug()<<"error select count(*) from Server";
    query.next();
    double sumSampling = query.value(0).toDouble();

    if(!seedUpLink) seedUpLink = 1;
    return (sumRate/sumSampling)/seedUpLink;
}

void seed_uplink_utilization(double *xval,double *yval,int *pointNum)//种子带宽利用率曲线图
{
    QSqlQuery query;
    int totalNum = 0;
    if(!query.exec("select Rate,uniID from Server where Type = 'S'"))
        qDebug()<<"error select Rate,uniID from Server";
    while(query.next())
    {
        xval[totalNum]=query.value(1).toDouble()*5;
        yval[totalNum]=query.value(0).toDouble()/seedUpLink;
        ++totalNum;
    }
    *pointNum = totalNum;
}
