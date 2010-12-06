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

    void do_file_Open();//打开文件
    bool do_file_Load(const QString& fileName);//读取文件
    void do_file_Save();//保存文件
    bool saveFile(const QString& fileName);//存储文件
    void do_action_Start();

private slots:
    void on_startBtn_clicked();
    void on_selectBtn_clicked();
};

#endif // ACTIONPAGE_H
