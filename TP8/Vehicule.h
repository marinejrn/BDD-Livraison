#ifndef VEHICULE_H
#define VEHICULE_H
#include <string>
#include <iostream>
#include "Chauffeur.h"
#include"Personne.h"

using namespace std;


class Vehicule {
protected : 
    string plaque;
    bool dispo;
public:
    Vehicule(string &plaque,bool dispo) :plaque(plaque),dispo(dispo) {}
    Vehicule() = default;
    virtual ~Vehicule() {}
    string getPlaque() { return plaque; }
    bool getDispo();
    void setDispo(bool disp);

    virtual void afficherInfos() = 0;  //Polymorphisme
    virtual void afficherType() = 0;
    static vector<Vehicule*> OuvrirFichierVehicule();
    static Vehicule* Affectation(const string& type);
    static void afficherListeVehicule();

};

#endif // VEHICULE_H

