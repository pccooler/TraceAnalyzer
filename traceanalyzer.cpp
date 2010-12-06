#include "traceanalyzer.h"
#include "ui_traceanalyzer.h"
#include "step1.h"
#include "step2.h"

TraceAnalyzer::TraceAnalyzer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TraceAnalyzer)
{
    ui->setupUi(this);

    //��ʼ��״̬��
    createStatusBar();

    //��ӱ�ǩҳ��
    Step1 *step1_p = new Step1();
    ui->tabWidget->addTab(step1_p,"Step1");
    Step2 *step2_p = new Step2();
    ui->tabWidget->addTab(step2_p,"Step2");
}

TraceAnalyzer::~TraceAnalyzer()
{
    delete ui;
}

void TraceAnalyzer::createStatusBar()
{
    QStatusBar* bar = ui->statusBar;
    statusLabel = new QLabel;
    statusLabel->setMinimumSize(150,20);
    bar->addWidget(statusLabel);
    statusLabel->setText("Ready");
}







