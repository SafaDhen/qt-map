#include "graph.h"
#include<QDebug>
#include<iostream>
#include<limits>
Graph::Graph() {}

void Graph::KnotenHinzuefugen(const QString Knoten)
{

    if(!Stadten.contains(Knoten))
    {
        Stadten.append(Knoten);
            // Adjacentliste.resize(Stadten.size());
        Adjacentliste.append(QList<QPair<QString, double>>());
    }
}

void Graph::KantenHinzuefugen(const QString Knoten1, const QString Knoten2, double distance)
{
    if (Stadten.contains(Knoten1) && Stadten.contains(Knoten2))
    {
        int index1 = Stadten.indexOf(Knoten1);
        int index2 = Stadten.indexOf(Knoten2);

        // Prüfe, ob die Kante von Knoten1 nach Knoten2 bereits existiert
        bool exists1 = false;
        const QList<QPair<QString, double>>& nachbarn1 = Adjacentliste[index1];
        for (int i = 0; i < nachbarn1.size(); ++i) {
            if (nachbarn1[i].first == Knoten2) {
                exists1 = true;
                break;
            }
        }

        // Prüfe, ob die Kante von Knoten2 nach Knoten1 bereits existiert
        bool exists2 = false;
        const QList<QPair<QString, double>>& nachbarn2 = Adjacentliste[index2];
        for (int i = 0; i < nachbarn2.size(); ++i) {
            if (nachbarn2[i].first == Knoten1) {
                exists2 = true;
                break;
            }
        }

        // Füge die Kante nur hinzu, wenn sie noch nicht existiert
        if (!exists1) {
            Adjacentliste[index1].append(qMakePair(Knoten2, distance));
        }
        if (!exists2) {
            Adjacentliste[index2].append(qMakePair(Knoten1, distance));
        }
    }
}

const QList<QPair<QString, double> > &Graph::getNachbarn(const QString &Knoten) const
{
    int index = Stadten.indexOf(Knoten);
    if (index != -1) {
        return Adjacentliste[index];
    }
    static QList<QPair<QString, double>> emptyList;
    return emptyList;
}

const QVector<QString> &Graph::getKnoten() const
{
    return Stadten;
}

void Graph::printGraph() const
{
    for (int i = 0; i < Adjacentliste.size(); ++i) {
        qDebug() << "Stadt: " << Stadten[i] << " ->";

        for (const QPair<QString, double>& pair : Adjacentliste[i]) {
            qDebug() << "   Nachbar: " << pair.first << " , Entfernung:" << pair.second;
        }
    }
}

QVector<QString> Graph::Dijstra(const QString &start, const QString &ziel, double &gesamtDistanz)
{
    QList<QPair<QString,double>>distanzen; // QList für Knoten und Distanzen
    QList<QPair<QString,QString>> vorgaenger; // Liste für vorgänger jedes Knotens
    QList< QString> unbesucht; // liste für unbesuchten Knoten

    // Initialisierung: Alle Distanzen auf unendlich setzen, außer Startknoten
    for (int i = 0; i < Stadten.size(); i++) {
        distanzen.append(qMakePair(Stadten[i], (Stadten[i] == start) ? 0.0 : qInf()));
        unbesucht.append(Stadten[i]);
    }

    while (!unbesucht.isEmpty()) {
        // Knoten mit der kleinsten Distanz finden
        QString aktuellerknoten;
        double miniDistanz = std::numeric_limits<double>::infinity();

        for (int i = 0; i < distanzen.size(); i++) {
            const auto &pair = distanzen[i];
            if (unbesucht.contains(pair.first) && pair.second < miniDistanz) {
                aktuellerknoten = pair.first;
                miniDistanz = pair.second;
            }
        }

        if (aktuellerknoten == ziel)
            break;

        unbesucht.removeOne(aktuellerknoten);

        int index = Stadten.indexOf(aktuellerknoten);
        for (int j = 0; j < Adjacentliste[index].size(); j++) {
            const auto &nachbar = Adjacentliste[index][j];
            QString nachbarName = nachbar.first;
            double kantenDistanz = nachbar.second;

            if (unbesucht.contains(nachbarName)) {
                double neueDistanz = miniDistanz + kantenDistanz;
                for (int i = 0; i < distanzen.size(); i++) {
                    auto &pair = distanzen[i];
                    if (pair.first == nachbarName && neueDistanz < pair.second) {
                        pair.second = neueDistanz;
                        vorgaenger.append(qMakePair(nachbarName, aktuellerknoten));
                        break;
                    }
                }
            }
        }
    }

    // Pfad rekonstruieren
    QVector<QString> pfad;
    QString knoten = ziel;
    for (int t = 0; t < distanzen.size(); t++) {
        const auto &pair = distanzen[t];
        if (pair.first == ziel) {
            gesamtDistanz = pair.second;
            break;
        }
    }

    while (true) {
        pfad.prepend(knoten);
        bool gefunden = false;
        for (int x = 0; x < vorgaenger.size(); x++) {
            if (vorgaenger[x].first == knoten) {
                knoten = vorgaenger[x].second;
                gefunden = true;
                break;
            }
        }
        if (!gefunden)
            break;
    }

    if ((!pfad.isEmpty()) && (pfad.first() != start) || (gesamtDistanz == qInf()))
        pfad.clear();

    return pfad;
}

void Graph::clearGraph()
{ if (Stadten.isEmpty() && Adjacentliste.isEmpty()) {
        return;  // Falls der Graph bereits leer ist, nichts tun
    }
    Stadten.clear();
    Adjacentliste.clear();
}

void Graph::knotenEntfernen(QString &knotenName)
{
    int index = Stadten.indexOf(knotenName);  // Index des Knotens finden
    if (index == -1) {
        qDebug() << "Knoten nicht gefunden: " << knotenName;
        return;  // Knoten nicht gefunden, nichts tun
    }



    // 1. Alle Verbindungen zu diesem Knoten aus anderen Knoten entfernen
    for (auto &nachbarn : Adjacentliste) {
        for (int i = 0; i < nachbarn.size(); ++i) {
            if (nachbarn[i].first == knotenName) {
                nachbarn.removeAt(i);
                break;
            }
        }
    }
    //2. Knoten aus der Liste entfernen
    Stadten.removeAt(index);
    Adjacentliste.removeAt(index);  // Alle Kanten des Knotens entfernen

}




