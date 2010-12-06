#ifndef TRACEANALYZER_H
#define TRACEANALYZER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QStatusBar>
#include <QLabel>



namespace Ui {
    class TraceAnalyzer;
}

class TraceAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TraceAnalyzer(QWidget *parent = 0);
    ~TraceAnalyzer();

private:
    Ui::TraceAnalyzer *ui;
    QLabel* statusLabel;

    void createStatusBar();//…Ë÷√◊¥Ã¨¿∏


private slots:
};

#endif // TRACEANALYZER_H
