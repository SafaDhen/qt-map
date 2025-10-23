#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QScrollArea>
#include<QPixmap>
#include<QLabel>
#include<QVBoxLayout>
#include<QTableWidget>
#include<QHeaderView>
#include<QTableWidgetItem>
#include<QDialog>
#include<QPainter>

#include<limits>
#include<QInputDialog>
#include<QMessageBox>
#include<sstream>
#include<fstream>
#include<cmath>
#include<QDebug>
#include<QFileDialog>
#include"adresse.h"
#include"poi.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pixW=ui->label->width();
    pixH=ui->label->height();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_1_Ort_Anlegen_triggered()
{
    if(MeinOrt.size()==0)
    {
        MeinOrt.push_back(myPosition);
    }

    // Typ des Ortes auswählen
    bool ok; // speichert, ob der Benutzer eine gültige Auswahl getroffen hat.
    QStringList ortstypen = {"Adresse", "Point of Interest"};
    QString typ = QInputDialog::getItem(this, "Ortstyp wählen", "Wählen Sie den Typ des Ortes:", ortstypen, 0, false, &ok);
    if (!ok) return;  // Abbruch

    // Eingabe der gemeinsamen Eigenschaften
    double laengengrad = QInputDialog::getDouble(this, "Längengrad eingeben", "Geben Sie den Längengrad ein (-180 bis 180):", 0.0, -180, 180, 6, &ok);
    if (!ok) return;  // Abbruch

    double breitengrad = QInputDialog::getDouble(this, "Breitengrad eingeben", "Geben Sie den Breitengrad ein (-90 bis 90):", 0.0, -90, 90, 6, &ok);
    if (!ok) return;  // Abbruch

    QString name = QInputDialog::getText(this, "Name eingeben", "Geben Sie den Namen des Ortes ein:", QLineEdit::Normal, "", &ok);
    if (!ok) return;  // Abbruch

    // Adresse erstellen
    if (typ == "Adresse") {
        QString strasse = QInputDialog::getText(this, "Straße eingeben", "Geben Sie die Straße ein:", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        int hausnummer = QInputDialog::getInt(this, "Hausnummer eingeben", "Geben Sie die Hausnummer ein:", 1, 1, 10000, 1, &ok);
        if (!ok) return;

        int postleitzahl = QInputDialog::getInt(this, "Postleitzahl eingeben", "Geben Sie die Postleitzahl ein:", 10000, 10000, 99999, 1, &ok);
        if (!ok) return;

        QString gemeinde = QInputDialog::getText(this, "Gemeinde eingeben", "Geben Sie die Gemeinde ein:", QLineEdit::Normal, "", &ok);
        if (!ok) return;
        //QString gemeinde = "hochschule";
        // Adresse erstellen und speichern
        string nameString=name.toStdString();
        string strassString=strasse.toStdString();
        string gemeindeString=gemeinde.toStdString();

        Adresse* PAdresse=new Adresse(laengengrad,breitengrad,'a',strassString,hausnummer,postleitzahl,gemeindeString,nameString);
        MeinOrt.push_back(PAdresse);
        AddRadioButton(nameString,breitengrad,laengengrad);
        knotenGraph.KnotenHinzuefugen(name);
         NachbarVerbinden(PAdresse);

        QMessageBox::information(this, "Erfolg", "Die Adresse wurde erfolgreich angelegt!");
    }
    // POI erstellen
    else if (typ == "Point of Interest") {
        QString bemerkung = QInputDialog::getText(this, "Bemerkung eingeben", "Geben Sie eine Bemerkung ein:", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        QString kategorie = QInputDialog::getText(this, "Kategorie eingeben", "Geben Sie die Kategorie ein (z.B. Restaurant, Tankstelle):", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        // POI erstellen und speichern
        string bemerkungString=bemerkung.toStdString();
        string kategorieString=kategorie.toStdString();
        string nameString=name.toStdString();

        PoI* pPoi=new PoI(laengengrad,breitengrad,'p',kategorieString,bemerkungString,nameString);
        MeinOrt.push_back(pPoi);
        AddRadioButton(nameString,breitengrad,laengengrad);
        knotenGraph.KnotenHinzuefugen(name);
       NachbarVerbinden(pPoi);

        QMessageBox::information(this, "Erfolg", "Der Point of Interest wurde erfolgreich angelegt!");
    }
}

void MainWindow::on_pushButton_Entfernung_clicked()
{
    QList<QRadioButton*> selectButton;

    for(auto& button:MeinButton)
    {
        if(button->isChecked())
        {
            selectButton.append(button);
        }
    }

    if (selectButton.size() != 2) {
        QMessageBox::warning(this, "Fehler", "Bitte wählen Sie genau zwei Orte aus.");
        return;
    }

    QString Name1=selectButton[0]->text();
    QString Name2=selectButton[1]->text();
    string NameString1=Name1.toStdString();
    string NameString2=Name2.toStdString();
    if(FindOrt(NameString1)==-1)
    {
        QMessageBox::information(this,"ERROR","Ort1 nicht gefunden");
    }
    else
    {
        if(FindOrt(NameString2)==-1)
        {
            QMessageBox::information(this,"ERROR","Ort2 nicht gefunden");
        }
        else
        {
            double result=Rechnung(*MeinOrt[FindOrt(NameString1)],*MeinOrt[FindOrt(NameString2)]);
            QString ResultSring=QString::number(result);
            QMessageBox::information(this,"Entfernung","Die Entfernung ist " + ResultSring+"2 km");
        }
    }

}


void MainWindow::on_pushButton_Information_clicked()
{
    /*QDialog dialog(this);  // Lokaler Dialog
    dialog.setWindowTitle("Navigationssystem - Orte anzeigen");
    dialog.resize(1200, 600);

    // QTableWidget erstellen
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "Typ", "Name", "Breitengrad", "Laengengrad","Parameter","Verbindung"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);*/

    QList<QRadioButton*> selectButton;

    for(auto& button:MeinButton)
    {
        if(button->isChecked())
        {
            selectButton.append(button);
        }
    }

    if (selectButton.size() !=1) {
        QMessageBox::warning(this, "Fehler", "Bitte wählen Sie genau einen Ort aus.");
        return;
    }

    QString Name1=selectButton[0]->text();

    string NameString1=Name1.toStdString();
    if(FindOrt(NameString1)==-1)
    {
        QMessageBox::information(this,"ERROR","Ort nicht gefunden");
    }
    else
    {
        Information(MeinOrt[FindOrt(NameString1)]);
    }
}


void MainWindow::on_pushButton_alle_Orte_clicked()
{
    if(MeinOrt.size()==0)
    {
        MeinOrt.push_back(myPosition);
    }
    QDialog dialog(this);  // Lokaler Dialog
    dialog.setWindowTitle("Navigationssystem - Orte anzeigen");
    dialog.resize(1200, 600);

    // QTableWidget erstellen
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "Typ", "Name", "Breitengrad", "Laengengrad", "Parameters","Verbindungen"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);



    int row=0;
    /*if(MeinOrt.size()==0)
    {
        QMessageBox::information(this,"ERROR","Kein Element  im Vector");

    }*/
    //else
    {
        for(auto ort : MeinOrt)
        {
            if(!ort) continue;

            table->insertRow(row);
            QString typ;
            QString parameters;
            QString  verbindung="";

            if(PoI* poi=dynamic_cast<PoI*>(ort))
            {
                typ="PoI";
                parameters= QString::fromStdString(poi->getKategorie()) +", "+ QString::fromStdString(poi->getBemerkung());

            }
            else if(Adresse* adresse=dynamic_cast<Adresse*>(ort))
            {

                typ="Adr";
                parameters=QString::fromStdString(adresse->getStrasse())+", "+
                             QString::number(adresse->getHausNummer())+", "+
                             QString::number(adresse->getPLZ())+", "+
                             QString::fromStdString(adresse->getGemeinde());

            }
            else
            {
                typ="Unbekant";
                parameters="Keine weiteren Parameters";
            }
            verbindung= QString::fromStdString(ort->getVerbindungen());

            table->setItem(row,0,new QTableWidgetItem(QString::number(ort->getID())));
            table->setItem(row,1,new QTableWidgetItem(typ));
            table->setItem(row,2,new QTableWidgetItem(QString::fromStdString(ort->getName())));
            table->setItem(row,3,new QTableWidgetItem(QString::number(ort->getBreitengrad())));
            table->setItem(row,4,new QTableWidgetItem(QString::number(ort->getLaengengrad())));
            table->setItem(row,5,new QTableWidgetItem(parameters));
            table->setItem(row,6,new QTableWidgetItem(verbindung));

            row++;
        }

        QVBoxLayout* layout=new QVBoxLayout(&dialog);
        layout->addWidget(table);

        dialog.setLayout(layout);
        dialog.exec();
    }
}


void MainWindow::on_pushButton_verschieben_clicked()
{
    bool ok; // speichert, ob der Benutzer eine gültige Auswahl getroffen hat.
    QStringList ortstypen = {"New Ort", "Existirende Ort"};
    QString typ = QInputDialog::getItem(this, "Ortstyp wählen", "Wählen Sie den Typ des Ortes:", ortstypen, 0, false, &ok);
    if (!ok) return;  // Abbruch
    if(typ=="Existirende Ort")
    {
        SchiebenExistierende();
        showPosition(MeinOrt[0]->getBreitengrad(),MeinOrt[0]->getLaengengrad(),
QString::fromStdString(MeinOrt[0]->getName()));
    }
    if(typ=="New Ort")
    {
        SchiebenNewOrt();
        showPosition(MeinOrt[0]->getBreitengrad(),MeinOrt[0]->getLaengengrad(),
QString::fromStdString(MeinOrt[0]->getName()));
    }
}


void MainWindow::on_pushButton_meinOrt_clicked()
{
    if(MeinOrt.size()==0)
    {
        MeinOrt.push_back(myPosition);
    }
    showPosition(MeinOrt[0]->getBreitengrad(),MeinOrt[0]->getLaengengrad(),
                 QString::fromStdString(MeinOrt[0]->getName()));
}


void MainWindow::on_action_2_Laden_triggered()
{
    // Dialogfenster zum Auswählen der Datei anzeigen
    QString filePath = QFileDialog::getOpenFileName(this, "Datei auswählen", "", "Textdateien (*.txt)");

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Abbruch", "Keine Datei ausgewählt.");
        return;  // Abbrechen, falls keine Datei ausgewählt wurde
    }

    // Überprüfen, ob bereits eine Karte geladen wurde
    if (!MeinOrt.empty()) {
        int result = QMessageBox::question(this, "Erneutes Laden",
                                           "Es wurden bereits Orte geladen. Möchten Sie die vorhandenen Orte löschen und eine neue Karte laden?",
                                           QMessageBox::Yes | QMessageBox::No);

        if (result == QMessageBox::No) {
            return;  // Abbrechen, falls der Benutzer nicht erneut laden möchte
        }

        // Vorhandene Orte löschen
        qDebug() << "Vorhandene Orte vor dem Löschen:" << MeinOrt.size();
        for (auto m : MeinOrt)
            delete m;
        MeinOrt.clear();
        qDebug() << "Orte erfolgreich gelöscht. " <<MeinOrt.size();
        knotenGraph.clearGraph();  // Graph ebenfalls leeren, falls nötig

        // for(auto b: MeinButton) //  programm crasch
        // {
        //    // b->hide();
        //     delete  b;
        // }
        // MeinButton.clear();
    }

    string nummerString, laengenString, BreitenString, HausnummerString, PLZString;
    string Strasse, Kategorie, Bemerkung, zeile, Gemeinde, Name,pName,Verbindungen;
    int Newnum = 0;
    int num = 0;
    int plz = 0;
    int Hausnummer = 0;
    double Breiten, Laengen;

    ifstream DateiIn(filePath.toStdString());
    if (!DateiIn) {
        QMessageBox::critical(this, "Fehler", "Datei konnte nicht geöffnet werden.");
        return;
    }

    if (MeinOrt.size() == 0) {
        MeinOrt.push_back(myPosition);
    }

    getline(DateiIn, zeile);

    while (getline(DateiIn, zeile)) {
        if (zeile == "POI")
            break;

        stringstream tmp(zeile);
        getline(tmp, nummerString, ';');
        getline(tmp, laengenString, ';');
        getline(tmp, BreitenString, ';');
        getline(tmp, Strasse, ';');
        getline(tmp, HausnummerString, ';');
        getline(tmp, PLZString, ';');
        getline(tmp, Gemeinde, ';');
        getline(tmp, Name, ';');
        getline(tmp,Verbindungen,';');

        stringstream SNummer(nummerString);
        stringstream SLaenge(laengenString);
        stringstream SBreiten(BreitenString);
        stringstream SHausnummer(HausnummerString);
        stringstream SPlz(PLZString);

        SNummer >> num;
        SLaenge >> Laengen;
        SBreiten >> Breiten;
        SHausnummer >> Hausnummer;
        SPlz >> plz;

        if (num != 0) {
            qDebug() << "Adresse geladen: "
                     << "Nummer:" << num
                     << ", Name:" << QString::fromStdString(Name)
                     << ", Laenge:" << Laengen
                     << ", Breite:" << Breiten;
            QString qName = QString::fromStdString(Name);
            Adresse* adresse = new Adresse(Laengen, Breiten, 'a', num, Strasse, Hausnummer, plz, Gemeinde, Name);
            adresse->setVerbindungen(Verbindungen);

            MeinOrt.push_back(adresse);
            AddRadioButton(Name, Breiten, Laengen);
            knotenGraph.KnotenHinzuefugen(qName);
        }

        if (num > Newnum) {
            Newnum = num;
        }
    }

    while (getline(DateiIn, zeile)) {
        if (zeile == " ")
            break;

        stringstream tmp(zeile);
        getline(tmp, nummerString, ';');
        getline(tmp, laengenString, ';');
        getline(tmp, BreitenString, ';');
        getline(tmp, Kategorie, ';');
        getline(tmp, Bemerkung, ';');
        getline(tmp, pName, ';');
        getline(tmp,Verbindungen,';');

        stringstream SNummer(nummerString);
        stringstream SLaenge(laengenString);
        stringstream SBreiten(BreitenString);

        SNummer >> num;
        SLaenge >> Laengen;
        SBreiten >> Breiten;

        if (num != 0) {
            qDebug() << "POI geladen: "
                     << "Nummer:" << num
                     << ", Name:" << QString::fromStdString(pName)
                     << ", Laenge:" << Laengen
                     << ", Breite:" << Breiten;
            QString qName = QString::fromStdString(pName);
            qDebug() << "pName: " << QString::fromStdString(pName);  // Ensure pName is correctly assigned
            PoI* Ppoi = new PoI(Laengen, Breiten, 'p', num, Kategorie, Bemerkung, pName);
            Ppoi->setVerbindungen(Verbindungen);
            MeinOrt.push_back(Ppoi);
            AddRadioButton(pName, Breiten, Laengen);
            knotenGraph.KnotenHinzuefugen(qName);
        }

        if (num > Newnum) {
            Newnum = num;
        }
    }

    DateiIn.close();
    QMessageBox::information(this, "Laden", "Orte erfolgreich geladen.");
    Ort::setNummer(Newnum);
    qDebug() << "Nummer: " << Newnum;

    // for (Ort* ort : MeinOrt) {
    //     if (ort->getID() != 0)
    //         NachbarVerbinden(ort);
    // }
    NachbarWiederherstellen();
    knotenGraph.printGraph();
}


/*
void MainWindow::on_action_2_Laden_triggered()
{
    // Datei öffnen
    QString filePath = QFileDialog::getOpenFileName(this, "Datei auswählen", "", "Textdateien (*.txt)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Abbruch", "Keine Datei ausgewählt.");
        return;
    }

    // Falls bereits Orte geladen wurden, nachfragen, ob sie gelöscht werden sollen
    if (!MeinOrt.empty()) {
        int result = QMessageBox::question(this, "Erneutes Laden",
                                           "Es wurden bereits Orte geladen. Möchten Sie die vorhandenen Orte löschen?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No) return;

        // Speicher freigeben
        qDebug() << "Lösche vorhandene Orte...";
        for (auto ort : MeinOrt) delete ort;
        MeinOrt.clear();
        knotenGraph.clearGraph();
    }

    // Datei öffnen
    std::ifstream DateiIn(filePath.toStdString());
    if (!DateiIn) {
        QMessageBox::critical(this, "Fehler", "Die Datei konnte nicht geöffnet werden.");
        return;
    }

    if (MeinOrt.empty()) MeinOrt.push_back(myPosition); // Startposition hinzufügen

    std::string zeile;
    int maxNummer = 0;

    // --- Adressen einlesen ---
    while (std::getline(DateiIn, zeile)) {
        if (zeile == "POI") break; // Ende der Adressliste erreicht

        std::stringstream ss(zeile);
        std::string nummerStr, laengenStr, breitenStr, strasse, hausnummerStr, plzStr, gemeinde, name, verbindungen;

        if (!std::getline(ss, nummerStr, ';') || !std::getline(ss, laengenStr, ';') ||
            !std::getline(ss, breitenStr, ';') || !std::getline(ss, strasse, ';') ||
            !std::getline(ss, hausnummerStr, ';') || !std::getline(ss, plzStr, ';') ||
            !std::getline(ss, gemeinde, ';') || !std::getline(ss, name, ';') ||
            !std::getline(ss, verbindungen, '\n'))
        {
            qDebug() << "⚠️ Fehler beim Einlesen der Zeile: " << QString::fromStdString(zeile);
            continue;
        }

        int nummer = std::stoi(nummerStr);
        double laenge = std::stod(laengenStr);
        double breite = std::stod(breitenStr);
        int hausnummer = std::stoi(hausnummerStr);
        int plz = std::stoi(plzStr);

        if (nummer == 0 || name.empty()) {
            qDebug() << "⚠️ Ungültige Adresse übersprungen: " << QString::fromStdString(zeile);
            continue;
        }

        qDebug() << "Adresse geladen: Nummer:" << nummer << ", Name:" << QString::fromStdString(name)
                 << ", Laenge:" << laenge << ", Breite:" << breite;

        Adresse* adresse = new Adresse(laenge, breite, 'a', nummer, strasse, hausnummer, plz, gemeinde, name);
        adresse->setVerbindungen(verbindungen);
        MeinOrt.push_back(adresse);
        AddRadioButton(name, breite, laenge);
        knotenGraph.KnotenHinzuefugen(QString::fromStdString(name));

        maxNummer = std::max(maxNummer, nummer);
    }

    // --- PoIs einlesen ---
    while (std::getline(DateiIn, zeile)) {
        if (zeile.empty()) break;

        std::stringstream ss(zeile);
        std::string nummerStr, laengenStr, breitenStr, kategorie, bemerkung, poiName, verbindungen;

        if (!std::getline(ss, nummerStr, ';') || !std::getline(ss, laengenStr, ';') ||
            !std::getline(ss, breitenStr, ';') || !std::getline(ss, kategorie, ';') ||
            !std::getline(ss, bemerkung, ';') || !std::getline(ss, poiName, ';') ||
            !std::getline(ss, verbindungen, '\n'))
        {
            qDebug() << "⚠️ Fehler beim Einlesen der PoI-Zeile: " << QString::fromStdString(zeile);
            continue;
        }

        int nummer = std::stoi(nummerStr);
        double laenge = std::stod(laengenStr);
        double breite = std::stod(breitenStr);

        if (nummer == 0 || poiName.empty()) {
            qDebug() << "⚠️ Ungültiger PoI übersprungen: " << QString::fromStdString(zeile);
            continue;
        }

        qDebug() << "PoI geladen: Nummer:" << nummer << ", Name:" << QString::fromStdString(poiName)
                 << ", Laenge:" << laenge << ", Breite:" << breite;

        PoI* poi = new PoI(laenge, breite, 'p', nummer, kategorie, bemerkung, poiName);
        poi->setVerbindungen(verbindungen);
        MeinOrt.push_back(poi);
        AddRadioButton(poiName, breite, laenge);
        knotenGraph.KnotenHinzuefugen(QString::fromStdString(poiName));

        maxNummer = std::max(maxNummer, nummer);
    }

    DateiIn.close();
    QMessageBox::information(this, "Laden", "Orte erfolgreich geladen.");
    Ort::setNummer(maxNummer);

    qDebug() << "Maximale Nummer: " << maxNummer;
    NachbarWiederherstellen();
    knotenGraph.printGraph();
}
*/
void MainWindow::on_action_3_Speichern_triggered()
{
    vector<Ort*> MeinAdresse;
    vector<Ort*>MeinPoI;
    for(auto m:MeinOrt)
    {
        if(m->getType()=='a')
            MeinAdresse.push_back(m);
        else
            MeinPoI.push_back(m);
    }

    ofstream DateiOut;
    DateiOut.open("Karte.txt");
    if(!DateiOut)
    {
        //cerr<< "Datei konnte  nicht geoffnet werden   "<<endl;
        exit(-1);
    }
    DateiOut<<"Adresse" <<'\n';

    for(auto A:MeinAdresse)
    {
        Adresse* PAdresse=dynamic_cast<Adresse*>(A);
        if(PAdresse)
        {
            DateiOut<<PAdresse->getID()<<';'
                     <<PAdresse->getLaengengrad()<<';'
                     <<PAdresse->getBreitengrad()<<';'
                     <<PAdresse->getStrasse()<<';'
                     <<PAdresse->getHausNummer()<<';'
                     <<PAdresse->getPLZ()<<';'
                     <<PAdresse->getGemeinde()<<';'
                     <<PAdresse->getName() <<';'
                     <<PAdresse->getVerbindungen()<<'\n';

        }
    }
    DateiOut<<"POI"<<'\n';

    for(auto P:MeinPoI)
    {
        PoI* PPoi=dynamic_cast<PoI*>(P);
        if(PPoi)
        {
            DateiOut<<PPoi->getID()<<';'
                     <<PPoi->getLaengengrad()<<';'
                     <<PPoi->getBreitengrad()<<';'
                     <<PPoi->getKategorie()<<';'
                     <<PPoi->getBemerkung()<<';'
                     <<PPoi->getName()<<';'
                     <<PPoi->getVerbindungen()<<'\n';

        }
    }
    DateiOut.close();
    // cout<<"Ort erfolgreich gespeichert " <<endl;
    QMessageBox::information(this,"Speichern","Orte erfolgreich gespeichert");
}
int MainWindow::FindOrt(const string name)
{

    for(unsigned int i =0; i<MeinOrt.size();i++)
    {
        if(MeinOrt[i]->getName()==name && MeinOrt[i]->getID()!=0)
        {

            return i;
        }
    }
    return -1;
}

int MainWindow::FindOrt(int num)
{
    for(unsigned int i =0; i<MeinOrt.size();i++)
    {
        if(MeinOrt[i]->getID()==num)
        {
            return  i;
        }
    }
    return -1;
}
double MainWindow::Rechnung(const Ort &ort1, const Ort &ort2)
{
    const double R=6371.0; //Erdradius
    double Laengen1 = Convert(ort1.getLaengengrad());
    double Breiten1 = Convert(ort1.getBreitengrad());
    double Laengen2 = Convert(ort2.getLaengengrad());
    double Breiten2 = Convert(ort2.getBreitengrad());


    double DeltaLaengen = Laengen2 - Laengen1;
    double DeltaBreiten = Breiten2 - Breiten1;

    // double a= sin(DeltaBreiten/2)*sin(DeltaBreiten)+cos(Breiten1)*cos(Breiten2)*sin(DeltaLaengen/2)*sin(DeltaLaengen);



    // double c= 2*atan2(sqrt(a),sqrt(1-a));

    // double result= R*c;
    double a = sin(DeltaBreiten / 2) * sin(DeltaBreiten / 2) +
               cos(Breiten1) * cos(Breiten2) * sin(DeltaLaengen / 2) * sin(DeltaLaengen / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    // Calcul final de la distance
    double result = R * c;


    return result;
}


double MainWindow::Convert(double value)
{
     return value*M_PI/180.0;
}
void MainWindow::Information(Ort *ort)
{
    QDialog dialog(this);  // Lokaler Dialog
    dialog.setWindowTitle("Navigationssystem - Orte anzeigen");
    dialog.resize(1200, 600);

    // QTableWidget erstellen
    QTableWidget* table = new QTableWidget(&dialog);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "Typ", "Name", "Breitengrad", "Laengengrad","Parameters","Verbindungen"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setMinimumSectionSize(600); // Mindestbreite für alle Spalten
    table->resizeColumnsToContents(); // Automatisches Anpassen der Spaltenbreite
    table->setColumnWidth(5, table->columnWidth(5) + 300); // "Parameters" etwas breiter machen
    table->setColumnWidth(6, table->columnWidth(6) + 300); // "Verbindungen" etwas breiter machen
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->insertRow(0);

    QString typ;
    QString parameters;

    if(PoI* poi=dynamic_cast<PoI*>(ort))
    {
        typ="PoI";
        parameters= QString::fromStdString(poi->getKategorie()) +", "+ QString::fromStdString(poi->getBemerkung());

    }
    else if(Adresse* adresse=dynamic_cast<Adresse*>(ort))
    {

        typ="Adr";
        parameters=QString::fromStdString(adresse->getStrasse())+", "+
                     QString::number(adresse->getHausNummer())+", "+
                     QString::number(adresse->getPLZ())+", "+
                     QString::fromStdString(adresse->getGemeinde());
    }
    else
    {
        typ="Unbekant";
        parameters="Keine weiteren Parameters";
    }
    QString Verbindungen=QString::fromStdString(ort->getVerbindungen());

    table->setItem(0,0,new QTableWidgetItem(QString::number(ort->getID())));
    table->setItem(0,1,new QTableWidgetItem(typ));
    table->setItem(0,2,new QTableWidgetItem(QString::fromStdString(ort->getName())));
    table->setItem(0,3,new QTableWidgetItem(QString::number(ort->getBreitengrad())));
    table->setItem(0,4,new QTableWidgetItem(QString::number(ort->getLaengengrad())));
    table->setItem(0,5,new QTableWidgetItem(parameters));
    table->setItem(0,6,new  QTableWidgetItem(Verbindungen));
    QVBoxLayout* layout=new QVBoxLayout(&dialog);
    layout->addWidget(table);

     QMessageBox::information(this,"Verbindungen",Verbindungen);

    dialog.setLayout(layout);
    dialog.exec();
}
void MainWindow::SchiebenExistierende()
{
    bool ok;
    QString nameString  = QInputDialog::getText(this, "Ort Name eingeben", "Geben Sie ein Ort Name an:", QLineEdit::Normal,"" ,&ok);
    if (!ok) return;
    string name=nameString.toStdString();
    if(FindOrt(name)!=0&& FindOrt(name)!=-1)
    {
        if(Adresse* adresse=dynamic_cast<Adresse*>(MeinOrt[FindOrt(name)]))
        {


            MeinOrt[0]=new Adresse(adresse->getLaengengrad(),adresse->getBreitengrad(),'a',0,
                                     adresse->getStrasse(),adresse->getHausNummer(),adresse->getPLZ(),adresse->getGemeinde(),adresse->getName());
            QMessageBox::information(this,"Erfolg","MeinOrt erfolgreich geschoben");
        }
        else if(PoI* poi=dynamic_cast<PoI*>(MeinOrt[FindOrt(name)]))
        {


            MeinOrt[0]=new PoI(poi->getLaengengrad(),poi->getBreitengrad(),'p',0,poi->getKategorie(),poi->getBemerkung(),poi->getName());
            QMessageBox::information(this,"Erfolg","MeinOrt erfolgreich geschoben");
        }

    }
    else
        QMessageBox::information(this,"ERROR","Mein Ort kann nicht verschoben sein");
}
void MainWindow::SchiebenNewOrt()
{
    bool ok; // speichert, ob der Benutzer eine gültige Auswahl getroffen hat.
    QStringList ortstypen = {"Adresse", "Point of Interest"};
    QString typ = QInputDialog::getItem(this, "Ortstyp wählen", "Wählen Sie den Typ des Ortes:", ortstypen, 0, false, &ok);
    if (!ok) return;  // Abbruch
    // Eingabe der gemeinsamen Eigenschaften
    double laengengrad = QInputDialog::getDouble(this, "Längengrad eingeben", "Geben Sie den Längengrad ein (-180 bis 180):", 0.0, -180, 180, 6, &ok);
    if (!ok) return;  // Abbruch

    double breitengrad = QInputDialog::getDouble(this, "Breitengrad eingeben", "Geben Sie den Breitengrad ein (-90 bis 90):", 0.0, -90, 90, 6, &ok);
    if (!ok) return;  // Abbruch

    QString name = QInputDialog::getText(this, "Name eingeben", "Geben Sie den Namen des Ortes ein:", QLineEdit::Normal, "", &ok);
    if (!ok) return;  // Abbruch

    // Adresse erstellen
    if (typ == "Adresse") {
        QString strasse = QInputDialog::getText(this, "Straße eingeben", "Geben Sie die Straße ein:", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        int hausnummer = QInputDialog::getInt(this, "Hausnummer eingeben", "Geben Sie die Hausnummer ein:", 1, 1, 10000, 1, &ok);
        if (!ok) return;

        int postleitzahl = QInputDialog::getInt(this, "Postleitzahl eingeben", "Geben Sie die Postleitzahl ein:", 10000, 10000, 99999, 1, &ok);
        if (!ok) return;

        QString gemeinde = QInputDialog::getText(this, "Gemeinde eingeben", "Geben Sie die Gemeinde ein:", QLineEdit::Normal, "", &ok);
        if (!ok) return;
        //QString gemeinde = "hochschule";
        // Adresse erstellen und speichern
        string nameString=name.toStdString();
        string strassString=strasse.toStdString();
        string gemeindeString=gemeinde.toStdString();


        Adresse* adresse=new Adresse(laengengrad,breitengrad,'a',strassString,hausnummer,postleitzahl,gemeindeString,nameString);
        MeinOrt.push_back(adresse);
        AddRadioButton(nameString,breitengrad,laengengrad);
        NachbarVerbinden(adresse);
        MeinOrt[0]=new Adresse(laengengrad,breitengrad,'a',0,strassString,hausnummer,postleitzahl,gemeindeString,nameString);
        QMessageBox::information(this, "Erfolg", "Mein  Position  erfolgreich zu eine Neu Adresse hinzüfugen");
    }
    // POI erstellen
    else if (typ == "Point of Interest") {
        QString bemerkung = QInputDialog::getText(this, "Bemerkung eingeben", "Geben Sie eine Bemerkung ein:", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        QString kategorie = QInputDialog::getText(this, "Kategorie eingeben", "Geben Sie die Kategorie ein (z.B. Restaurant, Tankstelle):", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        // POI erstellen und speichern
        string bemerkungString=bemerkung.toStdString();
        string kategorieString=kategorie.toStdString();
        string nameString=name.toStdString();



        PoI* poi= new PoI(laengengrad,breitengrad,'p',kategorieString,bemerkungString,nameString);
        MeinOrt.push_back(poi);
        AddRadioButton(nameString,breitengrad,laengengrad);
         NachbarVerbinden(poi);
         MeinOrt[0]=new PoI(laengengrad,breitengrad,'p',0,kategorieString,bemerkungString,nameString);
        QMessageBox::information(this, "Erfolg", "Mein Position erfolgreich zu einen neuen POI verchoben!");
    }
}
Ort* MainWindow::FindNachbar(Ort *ort)
{

    if(MeinOrt.empty())
        return nullptr;
    if(!ort || ort->getID()==0)
        return nullptr;

    Ort* Nachbar = nullptr;
    double MinDistance=numeric_limits<double>::max();

    for(Ort* POrt : MeinOrt )
    {
        double distance = Rechnung(*ort,*POrt);
        if(distance<MinDistance && distance!=0)
        {
            MinDistance=distance;
            Nachbar= POrt;
        }
    }
    return Nachbar;
}
QList<Ort*> MainWindow::FindNaechsteNachbarn(Ort *ort, int numNachbarn)
{
    if (MeinOrt.empty())
        return {};
    if (!ort || ort->getID() == 0)
        return {};

    QList<QPair<Ort*, double>> distanzListe; // Liste der Nachbarn mit Distanzen

    // Berechne die Entfernung zu allen anderen Orten
    for (Ort* POrt : MeinOrt) {
        double distance = Rechnung(*ort, *POrt);
        if (distance != 0) { // Sich selbst ausschließen (distance != 0)
            distanzListe.append(qMakePair(POrt, distance));
        }
    }

    // Sortiere die Liste nach der Entfernung
    std::sort(distanzListe.begin(), distanzListe.end(), [](const QPair<Ort*, double> &a, const QPair<Ort*, double> &b) {
        return a.second < b.second; // Aufsteigend nach Entfernung sortieren
    });

    // Erstelle die Liste der nächsten Nachbarn
    QList<Ort*> naechsteNachbarn;
    for (int i = 0; i < std::min(numNachbarn, static_cast<int>(distanzListe.size())); ++i) {
        naechsteNachbarn.append(distanzListe[i].first);

    }

    return naechsteNachbarn;
}
void  MainWindow::NachbarVerbinden(Ort *newOrt)
{
    if (MeinOrt.empty())
    {
        QMessageBox::warning(this, "Fehler", "Die Liste der Orte ist leer!");
        return;
    }

    if (!newOrt || newOrt->getID() == 0)
    {
        QMessageBox::warning(this, "Fehler", "Ungültiger Ort!");
        return ;
    }


    QList<Ort*> NewList = FindNaechsteNachbarn(newOrt, 3);
    if (NewList.isEmpty()) {
        QMessageBox::warning(this, "Fehler", "Keine Nachbarn gefunden!");
        return ;
    }

    for ( int i = 0; i < NewList.size(); ++i) {

        Ort* ort = NewList[i];

        if(ort->getID()!=0)
        {
        QString name1 = QString::fromStdString(newOrt->getName());
        QString name2 = QString::fromStdString(ort->getName());
        //QMessageBox::information(this, "Fehler", "name"+name2);
        int num1 = FindRadioButton(name1);
        int num2 = FindRadioButton(name2);

        if (num1 != -1 && num2 != -1) {
            if (MeinButton[num1] != nullptr && MeinButton[num2] != nullptr) {
                QRadioButton* button1 = MeinButton[num1];
                QRadioButton* button2 = MeinButton[num2];
                LinienZeichen(button1, button2);
                double distance =Rechnung(*ort,*newOrt);
                knotenGraph.KantenHinzuefugen(name1,name2,distance);
                string altOrtVerbindung=ort->getVerbindungen();
                string altNewOrtVerbindung=newOrt->getVerbindungen();
                string newOrtVerbindung;
                string newNewOrtVverbbindung;
                string distanceString= std::to_string(distance);
                if(altOrtVerbindung==""){
                    newOrtVerbindung= newOrt->getName()+"("+distanceString+")";
                }
                else{
                    newOrtVerbindung = altOrtVerbindung+","+newOrt->getName()+"("+distanceString+")";
                }
                if(altNewOrtVerbindung==""){
                    newNewOrtVverbbindung= ort->getName()+"("+distanceString+")";
                }
                else{
                    newNewOrtVverbbindung=altNewOrtVerbindung+","+ort->getName()+"("+distanceString+")";
                }
                ort->setVerbindungen(newOrtVerbindung);
                newOrt->setVerbindungen(newNewOrtVverbbindung);

                ort->newNachbar(newOrt->getName(),distance);
                newOrt->newNachbar(ort->getName(),distance);
            }
        } else {
            QMessageBox::warning(this, "Fehler", "Radio-Button für einen der Nachbarn nicht gefunden!");
            return;

        }
    }
    }
}
int MainWindow::FindRadioButton(QString Name)
{

    for(unsigned int i=0; i<MeinButton.size();i++)
    {
        if(MeinButton[i]->text()==Name)
        {

            return i;
        }
    }


    return -1;
}
void MainWindow::LinienZeichen(QRadioButton *button1, QRadioButton *button2)
{
    if (!button1 || !button2 || !ui->label )
    {
        QMessageBox::information(this,"Error", "Ungultige Zeiger");
        return; // Sicherheitsüberprüfung
    }

    // Abrufen der Geometrie der Buttons
    QRect rect1 = button1->geometry();
    QRect rect2 = button2->geometry();

    // Positionen der Kreise (linke obere Ecke + halbe Höhe für die Mitte des Kreises)
    QPoint center1 = rect1.topLeft() + QPoint(button1->height() / 2, button1->height() / 2);
    QPoint center2 = rect2.topLeft() + QPoint(button2->height() / 2, button2->height() / 2);

    // Offset relativ zum Parent (label)
    center1 = button1->parentWidget()->mapTo(ui->label, center1);
    center2 = button2->parentWidget()->mapTo(ui->label, center2);

    // Zeichnen der Linie auf der Karte (label)
    QPixmap pixmap = ui->label->pixmap(Qt::ReturnByValue);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::red, 3)); // Farbe und Breite der Linie
    painter.drawLine(center1, center2);
    painter.end();

    // Aktualisiere das Label mit dem neuen Pixmap
    ui->label->setPixmap(pixmap);
}

string MainWindow::NachbarSuchen(Ort * ort)
{
     string Verbindung=" ";
    vector<string> myNachbar=ort->getNachbar();
    vector<double>myDistance = ort->getDistance();
    if(myNachbar.size()!=0 && myDistance.size()!=0)
    {
        for(unsigned int  i=0; i<myNachbar.size();i++)
        {
            string distance= std::to_string(myDistance[i]);
            Verbindung=Verbindung+" "+ myNachbar[i]+"(" +distance + ")";
        }
    }
    return  Verbindung;
}

bool MainWindow::buttonChecked(QRadioButton*  button1, QRadioButton* button2)
{
    if(button1->isChecked() && button2->isChecked())
        return true;

    return false ;
}

void MainWindow::verbindungenEntfernen(string &name)
{
    if (MeinOrt.size()==0)
    {
        QMessageBox::information(this,"Error","Kein Ort gespeichert");
        return;
    }
    for(auto& ort: MeinOrt){
        string verbindungen = ort->getVerbindungen();
        if (verbindungen.empty()) continue;

        // Entferne den gelöschten Ort aus den Verbindungen
        QStringList verbindungsListe = QString::fromStdString(verbindungen).split(',');
        QStringList neueVerbindungen;

        for (int i=0; i<verbindungsListe.size();i++) {
            if (!verbindungsListe[i].contains(QString::fromStdString(name))) {
                neueVerbindungen.append(verbindungsListe[i]);  // Nur Verbindungen behalten, die nicht den gelöschten Ort enthalten
            }
        }

        // Setze die aktualisierten Verbindungen zurück
        ort->setVerbindungen(neueVerbindungen.join(',').toStdString());
    }
}
int MainWindow::gpsToPixelX(double gpsX)
{
    return ((gpsX - gpsTopLeftX) / (gpsBottomRightX - gpsTopLeftX)) * pixW;
}
int  MainWindow::gpsToPixelY(double gpsY)
{

   return ((gpsTopLeftY - gpsY) / (gpsTopLeftY - gpsBottomRightY)) * pixH;
}
void MainWindow::AddRadioButton(const string &name, const double &Breitengrad, const double Laengengrad)
{
    QString NameString=QString::fromStdString(name);

    QRadioButton* radio=new QRadioButton(ui->label);
    radio->setText(NameString);
    int w = gpsToPixelX(Laengengrad);//W=X
    int h = gpsToPixelY(Breitengrad);
    radio->setAutoExclusive(false);
    MeinButton.push_back(radio);
    radio->move(w,h);
    radio->show();
}

vector<Ort *> MainWindow::getMeinOrt() const
{
    return MeinOrt;
}

void MainWindow::RouteZeichen(QVector<QString> pfad)
{
    for(int i=0; i<pfad.size()-1;i++){
        QString  name1= pfad[i];
        QString name2= pfad[i+1];


        QRadioButton* button1= MeinButton[FindRadioButton(name1)];
        QRadioButton* button2= MeinButton[FindRadioButton(name2)];

        // Abrufen der Geometrie der Buttons
        QRect rect1 = button1->geometry();
        QRect rect2 = button2->geometry();

        // Positionen der Kreise (linke obere Ecke + halbe Höhe für die Mitte des Kreises)
        QPoint center1 = rect1.topLeft() + QPoint(button1->height() / 2, button1->height() / 2);
        QPoint center2 = rect2.topLeft() + QPoint(button2->height() / 2, button2->height() / 2);

        // Offset relativ zum Parent (label)
        center1 = button1->parentWidget()->mapTo(ui->label, center1);
        center2 = button2->parentWidget()->mapTo(ui->label, center2);

        // Zeichnen der Linie auf der Karte (label)
        QPixmap pixmap = ui->label->pixmap(Qt::ReturnByValue);
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::blue, 3)); // Farbe und Breite der Linie
        painter.drawLine(center1, center2);
        painter.end();

        // Aktualisiere das Label mit dem neuen Pixmap
        ui->label->setPixmap(pixmap);


    }
}

void MainWindow::KartenNeuzeichen()
{
    QPixmap pixmap = ui->label->pixmap(Qt::ReturnByValue);
   // pixmap.fill(Qt::transparent);  // Transparente Pixmap erstellen

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::red, 2));  // Rote Linien für die Verbindungen

    // Alle verbleibenden Verbindungen im Graphen zeichnen
    for (int i = 0; i < knotenGraph.getKnoten().size(); ++i) {
        QString startKnoten = knotenGraph.getKnoten()[i];
        const QList<QPair<QString, double>> &nachbarn = knotenGraph.getNachbarn(startKnoten);

        for (const auto &nachbar : nachbarn) {
            QString zielKnoten = nachbar.first;

            // Hole die Positionen der Buttons für die Knoten
            int indexStart = FindRadioButton(startKnoten);
            int indexZiel = FindRadioButton(zielKnoten);

            if (indexStart != -1 && indexZiel != -1) {
                QRect startRect= MeinButton[indexStart]->geometry();
                  QRect zielRect= MeinButton[indexZiel]->geometry();

                QPoint startPos = startRect.topLeft()+QPoint(MeinButton[indexStart]->height()/2,MeinButton[indexStart]->height()/2);
                QPoint zielPos = zielRect.topLeft()+QPoint(MeinButton[indexZiel]->height()/2,MeinButton[indexZiel]->height()/2);

                startPos = MeinButton[indexStart]->parentWidget()->mapTo(ui->label, startPos);
                zielPos = MeinButton[indexZiel]->parentWidget()->mapTo(ui->label, zielPos);

                painter.drawLine(startPos, zielPos);  // Linie zwischen den Orten zeichnen
            }
        }
    }

    painter.end();
    ui->label->setPixmap(pixmap);  // Aktualisierte Pixmap setzen
}

void MainWindow::NachbarWiederherstellen()
{
    for (auto& ort : MeinOrt) {
        if (ort->getID() != 0) {
            // Verbindungen des Ortes abrufen
            string Verbindungen = ort->getVerbindungen();
            if (Verbindungen.empty()) continue;  // Überspringe Orte ohne Verbindungen

            QString VerbindungenString = QString::fromStdString(Verbindungen);
            QString qName = QString::fromStdString(ort->getName());

            QStringList VerbindungsListe = VerbindungenString.split(',');
            for (const QString& verbindung : VerbindungsListe) {
                QStringList teilVerbindungen = verbindung.split('(');
                if (teilVerbindungen.size() == 2) {
                    QString nachbar = teilVerbindungen[0].trimmed();
                    bool ok = false;
                    double distanz = teilVerbindungen[1].remove(')').toDouble(&ok);

                    if (!ok) {
                        qDebug() << "Ungültige Distanz in Verbindung: " << verbindung;
                        continue;
                    }

                    int num1 = FindRadioButton(qName);
                    int num2 = FindRadioButton(nachbar);

                    // Index-Überprüfung, um Absturz zu vermeiden
                    if ( num2 !=-1 && num1 !=-1) {
                        if (MeinButton[num1] != nullptr && MeinButton[num2] != nullptr) {
                            QRadioButton* button1 = MeinButton[num1];
                            QRadioButton* button2 = MeinButton[num2];
                            LinienZeichen(button1, button2);

                            // Kante zum Graph hinzufügen
                            knotenGraph.KantenHinzuefugen(qName, nachbar, distanz);
                        }
                    } else {
                        qDebug() << "Ungültiger Index für RadioButton: " << qName << " oder " << nachbar;
                    }
                }
            }
        }
    }
}


vector<QRadioButton *> MainWindow::getMeinButton() const
{
    return MeinButton;
}
void MainWindow::showPosition(const double &Breitengrad, const double Laengengrad, QString Name)
{

    if(MeinLabel.size()==1)
    {
        MeinLabel[0]->hide();
        delete MeinLabel[0];
        MeinLabel.clear();

    }
    int  x=gpsToPixelX(Laengengrad);
    int y=gpsToPixelY(Breitengrad);

    QLabel* marker = new QLabel(ui->label);
    marker->setStyleSheet("background-color: green; color: white; border: 1px solid black;");
    marker->setToolTip("Mein Standort:"+Name);
    marker->setFixedSize(16, 16);
    marker->move(x , y);
    marker->lower();
    MeinLabel.push_back(marker);
    marker->show();
}

void MainWindow::on_Rooting_clicked()
{
    QList<QRadioButton*> selectButton;

    for(auto& button:MeinButton)
    {
        if(button->isChecked())
        {
            selectButton.append(button);
        }
    }

    if (selectButton.size() != 2) {

        return;
    }

    QString Name1=selectButton[0]->text();
    QString Name2=selectButton[1]->text();
    double distanz;
    QVector<QString> pfad = knotenGraph.Dijstra(Name1,Name2,distanz);

    if(pfad.isEmpty())
    {
        QMessageBox::information(this, "Fehler", "Kein Pfad gefunden.");
    }

    else{
        QString pfadText =" Kürzeste Pfad: ";

        for (int i=0; i< pfad.size(); i++){
            pfadText= pfadText + "->" +pfad[i];
        }
        pfadText= pfadText+" Gesamtdistanz: " + QString::number(distanz)+ " km";

        QMessageBox::information(this,"Erflog",pfadText);
        RouteZeichen(pfad);
    }


}


void MainWindow::on_Ort_Entfernen_clicked()
{
    QList<QRadioButton*> selectButton;

    for(auto& button:MeinButton)
    {
        if(button->isChecked())
        {
            selectButton.append(button);
        }
    }

    if (selectButton.size() >1 ||selectButton.size()==0) {
        QMessageBox::warning(this, "Fehler", "Bitte wählen Sie genau einen Ort aus.");
        return;
    }

    QString Name1=selectButton[0]->text();
    int index = FindRadioButton(Name1);
    if(index==-1){
    QMessageBox::warning(this, "Fehler", "Button nicht gefunden.");
        return;
    }
    else{
        MeinButton[index]->hide();

        delete MeinButton[index];
        MeinButton.erase(MeinButton.begin()+index);


        knotenGraph.knotenEntfernen(Name1);

        string name= Name1.toStdString();
        verbindungenEntfernen(name);
        int index2=FindOrt(name);
        if(index2!=1)
        {
            delete MeinOrt[index];
            MeinOrt.erase(MeinOrt.begin()+index2);
        }
        else{
            QMessageBox::warning(this, "Fehler", "Ort nicht gefunden.");
            return;
        }

    }
    QMessageBox::information(this, "Fehler", "Button erfolreich gelöscht.");
     KartenNeuzeichen();
}

