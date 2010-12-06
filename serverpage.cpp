#include "serverpage.h"
#include "ui_serverpage.h"

ServerPage::ServerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerPage)
{
    ui->setupUi(this);
}

ServerPage::~ServerPage()
{
    delete ui;
}
