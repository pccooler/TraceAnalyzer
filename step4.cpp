#include "step4.h"
#include "ui_step4.h"

#include <QColor>
#include <qpainter.h>
#include <qapplication.h>
#include <qframe.h>
#include <QDebug>
#include <QColor>
#include "func.h"

//extern  double xval[MaxValue];
//extern  double yval[MaxValue];
//extern  int pointNum;

Step4::Step4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Step4)
{
    ui->setupUi(this);



//    int i;
//    for(i=0; i<Size;i++)
//    {
//        xval[i] = double(i) * 10.0 / double(Size - 1);
//        yval[i] = qSin(xval[i]) * qCos(2.0 * xval[i]);
//    }



}

Step4::~Step4()
{
    delete ui;
}

void Step4::on_pushButton_clicked()
{
    qwtplot_p = new QwtPlot();
    qwtplot_p->setTitle(tr("这里是标题"));
    qwtplot_p->setAxisTitle(QwtPlot::xBottom,"this is x scale");
    qwtplot_p->setAxisTitle(QwtPlot::yLeft,"this is y scale");
    qwtplot_p->setCanvasBackground(QColor::fromRgb(255,255,255));
    qwtplot_p->resize(600,400);

    qwtplotgrid_p = new QwtPlotGrid();
    qwtplotgrid_p->enableY(true);
    qwtplotgrid_p->enableX(false);
    qwtplotgrid_p->setPen(Qt::DashDotLine);
    qwtplotgrid_p->attach(qwtplot_p);

    d_curves.setSymbol(new QwtSymbol(QwtSymbol::NoSymbol, Qt::NoBrush,
                                     QPen(Qt::black), QSize(5, 5) ) );
    d_curves.setPen(QColor(Qt::darkGreen));
    d_curves.setStyle(QwtPlotCurve::Lines);
    d_curves.setCurveAttribute(QwtPlotCurve::Fitted);

    d_curves.setRawSamples(xval,yval,50);
    d_curves.attach(qwtplot_p);
    qwtplot_p->show();
}
