#include "MainWindow.h"
#include <QApplication>
#include "qfonticon.h"
#include "Request.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontIcon::addFont(":/fontawesome.ttf");

    MainWindow w;
    w.show();

    return a.exec();
}
