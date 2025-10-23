#include "mainwindow.h"
#include"test_navi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Test_Navi test;
    QTest::qExec(&test);
    return a.exec();
}
