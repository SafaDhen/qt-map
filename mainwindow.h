#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>

#include"ort.h"
#include"myort.h"
#include<vector>
#include<QRadioButton>
#include<QLabel>
#include "graph.h"

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int FindOrt( const string  Name);
    int FindOrt(int num);
    double Rechnung(const Ort& ort1, const Ort& ort2);
    double Convert(double value);
    void Information(Ort *ort);
    void SchiebenExistierende();
    void SchiebenNewOrt();
    Ort* FindNachbar(Ort* ort);
    QList<Ort*> FindNaechsteNachbarn(Ort *ort, int numNachbarn);
    void NachbarVerbinden(Ort* newOrt);
    int FindRadioButton(QString Name);
    void LinienZeichen(QRadioButton* button1, QRadioButton* button2);
    string NachbarSuchen(Ort* ort);
    bool buttonChecked(QRadioButton *button1, QRadioButton *button2);
    void verbindungenEntfernen(string& name);

    vector<QRadioButton *> getMeinButton() const;

    vector<Ort *> getMeinOrt() const;
    void RouteZeichen(QVector<QString>pfad);
     void KartenNeuzeichen();
    void NachbarWiederherstellen();

private slots:
    void on_action_1_Ort_Anlegen_triggered();

    void on_pushButton_Entfernung_clicked();

    void on_pushButton_Information_clicked();

    void on_pushButton_alle_Orte_clicked();

    void on_pushButton_verschieben_clicked();

    void on_pushButton_meinOrt_clicked();

    void on_action_2_Laden_triggered();

    void on_action_3_Speichern_triggered();

    void on_Rooting_clicked();

    void on_Ort_Entfernen_clicked();


private:
    Ui::MainWindow *ui;

    const double gpsTopLeftX = 5.866;  // Längengrad (Longitude) des nordwestlichsten Punktes
    const double gpsTopLeftY = 55.058+0.3; // Breitengrad (Latitude) des nordwestlichsten Punktes

    const double gpsBottomRightX = 14.842+0.3;  // Längengrad (Longitude) des südöstlichsten Punktes ,plus peti a droite
    const double gpsBottomRightY = 48.051-0.8;  // Breitengrad (Latitude) des südöstlichsten Punktes,plus  grand dessans

    const double  laegenBerlin=13.3989;
    const double breitenBerlin=52.5109;
    const int Xberlin=329;
    const int Yberlin=426;

    const double  laegenkonstanz=9.17507;
    const double breitenkonstanz=47.6592;
    const int Xkonstanz=768;
    const int Ykonstanz=1174;

    int gpsToPixelX(double gpsX);
    int gpsToPixelY(double gpsY);



    const double LaenBerlin=13.3989367;
    const double BreitenBerlin=52.510885;

    void AddRadioButton(const string& name,const double& Breitengrad,const double Laengengrad);

    vector<Ort*> MeinOrt;
    vector<QRadioButton*>MeinButton;
    vector<QLabel*> MeinLabel;
    MyOrt* myPosition=new MyOrt(8.63991,49.8668,'p'," ",0,0," ","Hoschule Darmsatdt","Hoschule","Fachbereich Informatik");


    int pixW;
    int pixH;
    void showPosition(const double& Breitengrad,const double Laengengrad,QString Name);

    Graph knotenGraph;
    bool isliving=false;

};
#endif // MAINWINDOW_H
