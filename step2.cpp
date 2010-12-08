#include "step2.h"
#include "ui_step2.h"
#include "func.h"
#include <QString>


Step2::Step2(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Step2)
{
    ui->setupUi(this);
}

Step2::~Step2()
{
    delete ui;
}

void Step2::on_pushButton_clicked()
{
    func *func_p = new func();

    //输出节点平均下载时间
    QString adt;
    adt.setNum(func_p->avg_peer_download_time());
    ui->adtLE->setText(adt);

    //
}
