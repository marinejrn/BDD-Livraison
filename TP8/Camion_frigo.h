#ifndef CAMION_FRIGO_H
#define CAMION_FRIGO_H
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"   
#include <iostream>
#include <string>
#include "Vehicule.h"

class Camion_frigo : public Vehicule
{
private : 
    static int quantiteDispo;
public:

    //bool requisitionnerCamionFrigo();
    // Méthode statique pour ajouter un camion frigo
    static void ajouterCamionFrigo(Camion_frigo* camion) {
        if (camion->getDispo()) {
            quantiteDispo++;
        }
    }

    // Méthode statique pour obtenir la quantité de camions frigo disponibles
    static int getQuantiteDispo() {
        return quantiteDispo;
    }
    Camion_frigo(string plaque, bool dispo) : Vehicule(plaque, dispo) {}
    Camion_frigo() = default;
    void MiseAJour();
    void afficherInfos()
    {
        if (!getDispo()) {
            cout << "camion frigorifique" << " / " + getPlaque() + " / " <<RED<< "indisponible" <<RESET<< endl;
        }
        else {
            cout << "camion frigorifique" << " / " + getPlaque() + " / " <<GREEN<< "disponible" <<RESET<< endl;

        }
    }
    virtual void afficherType() { cout << "Type : Camion frigorifique\nPlaque d'immatriculation : " << getPlaque() << endl; }

};
#endif
