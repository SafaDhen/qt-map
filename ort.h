#ifndef ORT_H
#define ORT_H
#include<string>
#include<vector>
using namespace std;
class Ort
{
public:
    Ort(double l, double b,char t,int n,string Na);
    Ort(double l, double b,char t,string Na);
    Ort& operator=(const Ort& other);
    virtual ~Ort();



    char getType() const;
    void setType(char newType);

    static int getNummer();
    static void
    setNummer(int newNummer);

    int getID() const;

    string getName() const;

    double getLaengengrad() const;

    double getBreitengrad() const;

    void setLaengengrad(double newLaengengrad);

    void setBreitengrad(double newBreitengrad);

    void setName(const string &newName);
    void newNachbar(string name,double distance);

    vector<string> getNachbar() const;

    vector<double> getDistance() const;

    bool getIsliving() const;
    void setIsliving(bool newIsliving);

    string getVerbindungen() const;
    void setVerbindungen(const string &newVerbindungen);

protected:
    string Name;
    double Laengengrad;
    double Breitengrad;
    char type;
    const int ID;
    static inline int Nummer=0;
     vector<string> Nachbar;
    vector<double> Distance;
     bool isliving=false;
    string Verbindungen="";
};

#endif // ORT_H
