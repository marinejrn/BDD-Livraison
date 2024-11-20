#ifndef CAMION_BENNE_H
#define CAMION_BENNE_H
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"   
#include <iostream>
#include <string>
#include "Vehicule.h"

class Camion_benne : public Vehicule
{
private : 
    static int quantiteDispo;
public : 
    static void ajouterCamionBenne(Camion_benne* camion) {
        if (camion->getDispo()) {
            quantiteDispo++;
        }
    }

    static int getQuantiteDispo() {
        return quantiteDispo;
    }
    //bool requisitionnerCamionBenne();
    Camion_benne(string plaque, bool dispo) : Vehicule(plaque, dispo) {}
    Camion_benne() = default;

    void MiseAJour();
     void afficherInfos(){
        if (!getDispo()) {
            cout << "camion benne" << " / " + getPlaque() + " / " <<RED<< "indisponible"<<RESET << endl;
        }
        else {
            cout << "camion benne" << " / " + getPlaque() + " / " <<GREEN<< "disponible"<<RESET << endl;

        }
    }
     void afficherType() { cout << "Type : Camion benne\nPlaque d'immatriculation : " << getPlaque() << endl; }
};

#endif