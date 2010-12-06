#include "traceanalyzer.h"
#include "ui_traceanalyzer.h"
#include "step1.h"

TraceAnalyzer::TraceAnalyzer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TraceAnalyzer)
{
    ui->setupUi(this);

    //��ʼ��״̬��
    createStatusBar();

    //���Action��ǩҳ��
    ActionPage *actionPage = new ActionPage();
    ui->tabWidget->addTab(actionPage,"Action");
    Step1 *step1 = new Step1();
    ui->tabWidget->insertTab(0,step1,"Step1");
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







