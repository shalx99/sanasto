#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QString( "plastique"));
    MainWindow* w = MainWindow::getInstance();
    w->show();

    return a.exec();
}
