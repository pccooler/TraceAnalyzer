#ifndef STEP3_H
#define STEP3_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
    class Step3;
}

class Step3 : public QWidget
{
    Q_OBJECT

public:
    explicit Step3(QWidget *parent = 0);
    ~Step3();

private:
    Ui::Step3 *ui;
    QSqlTableModel *model;

private slots:
    void on_pushButton_clicked();
};

#endif // STEP3_H
