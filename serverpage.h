#ifndef SERVERPAGE_H
#define SERVERPAGE_H

#include <QWidget>

namespace Ui {
    class ServerPage;
}

class ServerPage : public QWidget
{
    Q_OBJECT

public:
    explicit ServerPage(QWidget *parent = 0);
    ~ServerPage();

private:
    Ui::ServerPage *ui;
};

#endif // SERVERPAGE_H
