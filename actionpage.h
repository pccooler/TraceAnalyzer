#ifndef ACTIONPAGE_H
#define ACTIONPAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QSqlQuery>
#include "action.h"

namespace Ui {
    class ActionPage;
}

class ActionPage : public QWidget
{
    Q_OBJECT

public:
    explicit ActionPage(QWidget *parent = 0);
    ~ActionPage();

private:
    Ui::ActionPage *ui;
    QStringList fileNames;
    Action *action_p;

    void do_file_Open();//���ļ�
    bool do_file_Load(const QString& fileName);//��ȡ�ļ�
    void do_file_Save();//�����ļ�
    bool saveFile(const QString& fileName);//�洢�ļ�
    void do_action_Start();

private slots:
    void on_startBtn_clicked();
    void on_selectBtn_clicked();
};

#endif // ACTIONPAGE_H
