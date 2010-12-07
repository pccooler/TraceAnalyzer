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
                        QString num = numlist.value(0);
                        num = num.mid(line.indexOf("(")+1);
                        filePieceNum = num.toDouble();
                        qDebug()<<filePieceNum;
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
