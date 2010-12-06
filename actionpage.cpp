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


void ActionPage::do_file_Open()//���ļ�
{
    fileNames = QFileDialog::getOpenFileNames(this);//һ���Զ�ȡ�򿪶���ļ�

    QString outTextEdit;
    foreach(QString fileName,fileNames)
    {
        outTextEdit += fileName.mid(fileName.lastIndexOf("/")+1)+"\n";
    }
    ui->filenamesTe->setText(outTextEdit);
}

bool ActionPage::do_file_Load(const QString& fileName)//��ȡ�ļ�
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("��ȡ�ļ�"),tr("�޷���ȡ�ļ� %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QString line;


    if(fileName.contains(QRegExp(".*/action..*")))//������ʽƥ��action�ļ�
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
        //��ֻд��ʽ���ļ��������ʧ���򵯳���ʾ�򲢷���
    {
        QMessageBox::warning(this,tr("�����ļ�"),
                             tr("�޷������ļ� %1:\n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    return true;
}

void ActionPage::do_file_Save()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("���Ϊ"));
    saveFile(fileName);
}

void ActionPage::do_action_Start()//������ʼ
{
    foreach(QString fileName,fileNames)
        //����򿪶���ļ�
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

