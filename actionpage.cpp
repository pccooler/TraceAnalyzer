#include "actionpage.h"
#include "ui_actionpage.h"

ActionPage::ActionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionPage)
{
    ui->setupUi(this);
}

ActionPage::~ActionPage()
{
    delete ui;
}


void ActionPage::do_file_Open()//打开文件
{
    fileNames = QFileDialog::getOpenFileNames(this);//一次性读取打开多个文件

    QString outTextEdit;
    foreach(QString fileName,fileNames)
    {
        outTextEdit += fileName.mid(fileName.lastIndexOf("/")+1)+"\n";
    }
    ui->filenamesTe->setText(outTextEdit);
}

bool ActionPage::do_file_Load(const QString& fileName)//读取文件
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("读取文件"),tr("无法读取文件 %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QString line;


    if(fileName.contains(QRegExp(".*/action..*")))//正则表达式匹配action文件
    {
        action_p = new Action();

        line = in.readLine();
        while(!line.isNull())
        {
            QStringList list = line.split(" ");
            action_p->setAction(list.value(0));
            action_p->setTime(list.value(1));
            action_p->setPeer(list.value(2));
            action_p->do_insert_DB();
            line = in.readLine();
        }
        delete action_p;
        action_p = NULL;
        return true;
    }
    return false;
}

bool ActionPage::saveFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
        //以只写方式打开文件，如果打开失败则弹出提示框并返回
    {
        QMessageBox::warning(this,tr("保存文件"),
                             tr("无法保存文件 %1:\n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    return true;
}

void ActionPage::do_file_Save()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"));
    saveFile(fileName);
}

void ActionPage::do_action_Start()//分析开始
{
    foreach(QString fileName,fileNames)
        //处理打开多个文件
    {
        if(!fileName.isEmpty())
        {
            do_file_Load(fileName);
        }
    }

    action_p->do_query_DB();
    QString str;
    str.setNum(action_p->totalRecordNum());
    ui->totalnumEdit->setText(str);
    str.setNum(action_p->effectiveRecordNum());
    ui->effectivenumEdit->setText(str);
    str.setNum(action_p->ineffectiveRecordNum());
    ui->ineffectivenumEdit->setText(str);
    str.setNum(action_p->avgDownloadTime());
    ui->avgdownloadtimeEdit->setText(str);
}

void ActionPage::on_selectBtn_clicked()
{
    do_file_Open();
}

void ActionPage::on_startBtn_clicked()
{
    do_action_Start();
}

