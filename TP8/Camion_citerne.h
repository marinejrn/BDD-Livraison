#ifndef CAMION_CITERNE_H
#define CAMION_CITERNE_H
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"   
#include <iostream>
#include <string>
#include "Vehicule.h"

class Camion_citerne : public Vehicule
{
private : 
    static int quantiteDispo;
public : 
    Camion_citerne() = default;
    Camion_citerne(string plaque, bool dispo) : Vehicule(plaque, dispo) {}
    //bool requisitionnerCamionCiterne();
    static void ajouterCamionCiterne(Camion_citerne* camion) {
        if (camion->getDispo()) {
            quantiteDispo++;
        }
    }
    static int getQuantiteDispo() {
        return quantiteDispo;
    }

    void afficherInfos() {
        if (!getDispo()) {
            cout << "camion citerne" << " / " + getPlaque() + " / " <<RED<< "indisponible"<<RESET << endl;
        }
        else {
            cout << "camion citerne" << " / " + getPlaque() + " / " <<GREEN<< "disponible" <<RESET<< endl;

        }
    }
    void afficherType() { cout << "Type : Camion citerne\nPlaque d'immatriculation : " << getPlaque() << endl; }
    void MiseAJour();
};

#endif