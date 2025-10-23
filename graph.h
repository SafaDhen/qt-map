#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QString>
#include <QList>
#include <QDebug>
#include<string>
#include<QString>
using namespace std;
//#include"ort.h"
class Graph
{
public:
    Graph();
    void KnotenHinzuefugen(const QString Knoten);
    void KantenHinzuefugen(const QString Knoten1, const QString Knoten2, double distance);
    const QList<QPair<QString, double>>& getNachbarn(const QString &Knoten) const ;
    const QVector<QString>& getKnoten() const;
    void printGraph() const;
   // int KnotenSuchen(Qstring Name);
    QVector<QString> Dijstra (const QString & start, const QString  & ziel, double & gesamtDistanz);
    void clearGraph();
    void knotenEntfernen(QString & knotenName);
private:
    QVector<QString> Stadten;
    QVector<QList<QPair<QString ,double>>> Adjacentliste;

};

#endif // GRAPH_H
