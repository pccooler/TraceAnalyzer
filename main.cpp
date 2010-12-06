#include <QtGui/QApplication>
#include "traceanalyzer.h"
#include "DBconnection.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    if(!connect_DB())
        return false;

    TraceAnalyzer w;
    w.show();

//    close_DB();




    return a.exec();
}
