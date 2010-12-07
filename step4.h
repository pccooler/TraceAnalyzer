#ifndef STEP4_H
#define STEP4_H

#include <QWidget>
#include "Qwt/qwt_plot_curve.h"
#include "Qwt/qwt_scale_map.h"
#include "Qwt/qwt_symbol.h"
#include "Qwt/qwt_math.h"
#include "Qwt/qwt_plot.h"
#include "Qwt/qwt_plot_grid.h"

const int Size = 27;

namespace Ui {
    class Step4;
}

class Step4 : public QWidget
{
    Q_OBJECT

public:
    explicit Step4(QWidget *parent = 0);
    ~Step4();

private:
    Ui::Step4 *ui;

    double xval[Size];
    double yval[Size];
    QwtPlotCurve d_curves;
    QwtPlot *qwtplot_p;
    QwtPlotGrid *qwtplotgrid_p;



private slots:
    void on_pushButton_clicked();
};

#endif // STEP4_H
