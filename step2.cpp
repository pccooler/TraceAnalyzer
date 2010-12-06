#include "step2.h"
#include "ui_step2.h"

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
    QWidget *h_p = new QWidget();
    h_p->resize(200,200);
    h_p->show();
}
