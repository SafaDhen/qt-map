#include "test_navi.h"
#include"mainwindow.h"
#include"ort.h"
#include<QRadioButton>
Test_Navi::Test_Navi() {}

void Test_Navi::TestEntfernung()
{
    MainWindow Main;
    Ort* berlin= new Ort(13.3989367,52.510885,'p',10,"berlin");
    Ort* mainz = new Ort(8.2762513,50.0012314,'p',15,"mainz");

    QCOMPARE(Main.Rechnung(*berlin,*mainz),452.540752226);
}

void Test_Navi::TestEntfernungGleich()
{
    MainWindow Main;
    Ort* berlin= new Ort(13.3989367,52.510885,'p',10,"berlin");
    Ort* mainz = new Ort(8.2762513,50.0012314,'p',15,"mainz");

    double distance1= Main.Rechnung(*berlin,*mainz);
    double  distance2=Main.Rechnung(*mainz,*berlin);
   QCOMPARE(abs(distance1-distance2),0);
}

void Test_Navi::buttonChek()
{
    QRadioButton* button1= new QRadioButton();
    QRadioButton* button2 =new  QRadioButton();
    button1->setChecked(true);
     MainWindow Main;
    QCOMPARE(Main.buttonChecked(button1,button2),false);

}
