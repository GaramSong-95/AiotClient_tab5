#include "mainwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setWindowTitle("벌레퇴치로봇관리");
    w.show();
    return a.exec();
}
