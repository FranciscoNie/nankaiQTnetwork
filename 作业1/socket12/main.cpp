#include "mainwindow.h"
#include <QUdpSocket>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.readdata();
    w.show();

    return a.exec();
}
