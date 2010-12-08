#include "func.h"
#include "simsce.h"
#include "out.h"
#include "server.h"
#include "action.h"
#include "interaction.h"
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

const double pieceSize = 256;

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
                        qDebug()<<"runtime:"<<line;
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
                        filePieceNum = num.toDouble();
                        //获取seed上传带宽
                        num = numlist.value(3);
                        numlist = num.split(")");
                        num = numlist.value(0);
                        seedUpLink = num.toDouble();

                        qDebug()<<"filePieceNum:"<<filePieceNum<<"seedUpLink:"<<seedUpLink;
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
            if(fileName.contains(QRegExp(".*/[Ii]nter[Aa]ction.*")))//正则表达式匹配InterAction文件
            {
                InterAction *interaction_p = new InterAction();

                line = in.readLine();
                while(!line.isNull())
                {
                    interaction_p->setDate(line);
                    interaction_p->do_insert_DB();
                    line = in.readLine();
                }

                delete interaction_p;
                interaction_p = NULL;
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

void func::seed_uplink_utilization(double *xval,double *yval,int *pointNum)//种子带宽利用率曲线图
{
    QSqlQuery query;
    int totalNum = 0;
    if(!query.exec("select Rate,Time from Server where Type = 'S'"))
        qDebug()<<"error select Rate,Time from Server";
    while(query.next())
    {
        xval[totalNum]=query.value(1).toDouble();
        yval[totalNum]=query.value(0).toDouble()/seedUpLink;
        ++totalNum;
    }
    *pointNum = totalNum;
}

double func::seed_normalization()//种子归一化负载
{
    /*
需要输出种子归一化负载= 种子上传数据块总数/原始文件大小（文件块总个数，从I1中得到）
I3（保留）中能输出服务器输出流量速率(Mbps) <rate>
那么此处，种子上传数据块总数=  sum(rate) *固定时间间隔（记录周期）*1024/256/8

rate_ += 1024*pieceSize_+44*(1024*pieceSize_/1000+1);
app_->rate_*8/5/1024/1024);
*/
    QSqlQuery query;
    query.prepare("select Time from Server where Type = 'S' order by Time asc");
    query.exec();
    query.next();
    double d1 = query.value(0).toDouble();
    query.next();
    double d2 = query.value(0).toDouble();
    query.prepare("select sum(Rate) from Server where Type = 'S'");
    query.exec();
    query.next();
    double sumRate = query.value(0).toDouble();
    return sumRate*(d2-d1)*1024*1024/8/(1024*pieceSize+44*(1024*pieceSize/1000+1))/filePieceNum;

}

void func::interest_conct(double *xval,double *yval,int *pointNum)//感兴趣连接曲线图
{
    QSqlQuery query;
    int totalNum = 0;
    if(!query.exec("select Time,InterestConctNum from InterestConct"))
        qDebug()<<"error select Time,InterestConctNum from InterestConct";
    while(query.next())
    {
        xval[totalNum]=query.value(0).toDouble();
        yval[totalNum]=query.value(1).toDouble();
        ++totalNum;
    }
    *pointNum = totalNum;
}
