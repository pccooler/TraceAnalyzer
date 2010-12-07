#include "step3.h"
#include "ui_step3.h"
#include <QString>


Step3::Step3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step3)
{
    ui->setupUi(this);
    ui->comboBox->addItem("action");
    ui->comboBox->addItem("simsce");
    ui->comboBox->addItem("out");
    ui->comboBox->addItem("server");
    ui->comboBox->addItem("InterArrival");
    ui->comboBox->addItem("InterestConct");

}

Step3::~Step3()
{
    delete ui;
}

void Step3::on_pushButton_clicked()
{
    QString tableName = ui->comboBox->currentText();
    model = new QSqlTableModel();
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->tableView->setModel(model);
}
