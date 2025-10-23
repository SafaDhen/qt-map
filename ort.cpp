#include "ort.h"

Ort::Ort(double l, double b, char t,int n,string Na):Laengengrad(l),Breitengrad(b),type(t),ID(n),Name(Na) {}

Ort::Ort(double l, double b, char t,string Na):Laengengrad(l),Breitengrad(b),type(t),ID(++Nummer),Name(Na) {}

Ort &Ort::operator=(const Ort &other)
{
    if(this != &other)
    {
        this->Laengengrad=other.getLaengengrad();
        this->Breitengrad=other.getBreitengrad();
        this->type=other.getType();
    }
    return *this;
}

Ort::~Ort()
{

}





char Ort::getType() const
{
    return type;
}

void Ort::setType(char newType)
{
    type = newType;
}

int Ort::getNummer()
{
    return Nummer;
}

void Ort::setNummer(int newNummer)
{
    Nummer = newNummer;
}

int Ort::getID() const
{
    return ID;
}

string Ort::getName() const
{
    return Name;
}

double Ort::getLaengengrad() const
{
    return Laengengrad;
}

double Ort::getBreitengrad() const
{
    return Breitengrad;
}

void Ort::setLaengengrad(double newLaengengrad)
{
    Laengengrad = newLaengengrad;
}

void Ort::setBreitengrad(double newBreitengrad)
{
    Breitengrad = newBreitengrad;
}

void Ort::setName(const string &newName)
{
    Name = newName;
}

void Ort::newNachbar(string name, double distance)
{
    bool found = false;
    for(unsigned int i=0; i<Nachbar.size();i++)
    {
        if(Nachbar[i]==name)
        {
            found=true;
            break;
        }
    }
    if(!found)
    {
      Nachbar.push_back(name);
        Distance.push_back(distance);
    }
}

vector<string> Ort::getNachbar() const
{
    return Nachbar;
}

vector<double> Ort::getDistance() const
{
    return Distance;
}

bool Ort::getIsliving() const
{
    return isliving;
}

void Ort::setIsliving(bool newIsliving)
{
    isliving = newIsliving;
}

string Ort::getVerbindungen() const
{
    return Verbindungen;
}

void Ort::setVerbindungen(const string &newVerbindungen)
{
    Verbindungen = newVerbindungen;
}
