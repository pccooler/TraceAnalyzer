#include <QtGui/QApplication>
#include "traceanalyzer.h"
#include "DBconnection.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    if(!connect_DB())
        return false;
    if(!create_Table())
        return false;

    TraceAnalyzer w;
    w.show();

    return a.exec();
}
