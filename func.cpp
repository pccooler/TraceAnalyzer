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
                        qDebug()<<"runtime:"<<line;
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
                        filePieceNum = num.toDouble();
                        //��ȡseed�ϴ�����
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
            if(fileName.contains(QRegExp(".*/[Ii]nter[Aa]ction.*")))//������ʽƥ��InterAction�ļ�
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

void func::seed_uplink_utilization(double *xval,double *yval,int *pointNum)//���Ӵ�������������ͼ
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

double func::seed_normalization()//���ӹ�һ������
{
    /*
��Ҫ������ӹ�һ������= �����ϴ����ݿ�����/ԭʼ�ļ���С���ļ����ܸ�������I1�еõ���
I3��������������������������������(Mbps) <rate>
��ô�˴��������ϴ����ݿ�����=  sum(rate) *�̶�ʱ��������¼���ڣ�*1024/256/8

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

void func::interest_conct(double *xval,double *yval,int *pointNum)//����Ȥ��������ͼ
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
