#include "traceanalyzer.h"
#include "ui_traceanalyzer.h"
#include "step1.h"
#include "step2.h"
#include "step3.h"
#include "step4.h"

TraceAnalyzer::TraceAnalyzer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TraceAnalyzer)
{
    ui->setupUi(this);

    //初始化状态栏
    createStatusBar();

    //添加标签页面
    Step1 *step1_p = new Step1();
    ui->tabWidget->addTab(step1_p,"Step1");
    Step2 *step2_p = new Step2();
    ui->tabWidget->addTab(step2_p,"Step2");
    Step3 *step3_p = new Step3();
    ui->tabWidget->addTab(step3_p,"Step3");
    Step4 *step4_p = new Step4();
    ui->tabWidget->addTab(step4_p,"Step4");
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







