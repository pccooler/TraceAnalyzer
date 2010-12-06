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

            if(fileName.contains(QRegExp(".*/[Ss]imsce.*")))//正则表达式匹配action文件
            {

            }
            if(fileName.contains(QRegExp(".*/[Oo]ut.*")))//正则表达式匹配out文件
            {

            }
            if(fileName.contains(QRegExp(".*/[Ss]erver.*")))//正则表达式匹配server文件
            {

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
