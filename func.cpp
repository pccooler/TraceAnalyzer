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
        //����򿪶���ļ�
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

            if(fileName.contains(QRegExp(".*/out.*.0")))//������ʽƥ��out?.0�ļ�
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
            if(fileName.contains(QRegExp(".*/[Ss]im[Ss]ce.*")))//������ʽƥ��SimSce�ļ�
            {
                SimSce *simsce_p = new SimSce();
                line = in.readLine();
                while(!line.isNull())
                {
                    if(line.contains("[Sessions]"))
                    {
                        line = in.readLine();
                        QStringList numlist = line.split(",");
                        //��ȡ�ļ�����
                        QString num = numlist.value(0);
                        num = num.mid(line.indexOf("(")+1);
                        filePieceNum = num.toInt();
                        //��ȡseed�ϴ�����
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
            if(fileName.contains(QRegExp(".*/[Oo]ut.*")))//������ʽƥ��out�ļ�
            {

            }
            if(fileName.contains(QRegExp(".*/[Ss]erver.*")))//������ʽƥ��server�ļ�
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
            if(fileName.contains(QRegExp(".*/[Aa]ction.*")))//������ʽƥ��action�ļ�
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
        //��ֻд��ʽ���ļ��������ʧ���򵯳���ʾ�򲢷���
    {
        return false;
    }
    QTextStream out(&file);
    return true;
}

double func::avg_peer_download_time()//ƽ���ڵ�����ʱ��
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

double func::avg_seed_uplink_utilization()//ƽ�����Ӵ���������
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

void seed_uplink_utilization(double *xval,double *yval,int *pointNum)//���Ӵ�������������ͼ
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
