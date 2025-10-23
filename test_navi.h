#ifndef TEST_NAVI_H
#define TEST_NAVI_H
#include<QCoreApplication>
#include <QtTest/QtTest>
#include <QObject>

class Test_Navi:public QObject
{
    Q_OBJECT
public:
    Test_Navi();
private slots:
    void TestEntfernung();
    void TestEntfernungGleich();
    void buttonChek();
};

#endif // TEST_NAVI_H
