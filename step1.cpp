#include "step1.h"
#include "ui_step1.h"
#include "func.h"
#include <QFileDialog>
#include <QRegExp>

#include "action.h"
#include <QSqlQuery>
#include <QDebug>
#include <QTime>

Step1::Step1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step1)
{
    ui->setupUi(this);
}

Step1::~Step1()
{
    delete ui;
}

void Step1::on_browserBtn_clicked()
{
    fileNames = QFileDialog::getOpenFileNames(this);//一次性读取打开多个文件

    QString simsceTE;
    QString outTE;
    QString serverTE;
    QString actionTE;
    foreach(QString fileName,fileNames)
    {
        if(fileName.contains(QRegExp(".*/[Ss]imsce.*.tr")))
        simsceTE += fileName.mid(fileName.lastIndexOf("/")+1)+"\n";
        if(fileName.contains(QRegExp(".*/[Oo]ut.*.tr")))
        outTE += fileName.mid(fileName.lastIndexOf("/")+1)+"\n";
        if(fileName.contains(QRegExp(".*/[Ss]erver.*.tr")))
        serverTE += fileName.mid(fileName.lastIndexOf("/")+1)+"\n";
        if(fileName.contains(QRegExp(".*/[Aa]ction.*.tr")))
        actionTE += fileName.mid(fileName.lastIndexOf("/")+1)+"\n";
    }
    ui->simsceTE->setText(simsceTE);
    ui->outTE->setText(outTE);
    ui->serverTE->setText(serverTE);
    ui->actionTE->setText(actionTE);
}

void Step1::on_startBtn_clicked()
{
    func *func_p = new func();
    func_p->do_load_file(fileNames);

    Action *action_p = new Action();
    action_p->do_query_DB();
}
