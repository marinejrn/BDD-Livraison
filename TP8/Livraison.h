#ifndef LIVRAISON_H
#define LIVRAISON_H
#pragma once
#include "Commande.h"
#include "Vehicule.h"
#include "Camion_frigo.h"
#include "Camion_benne.h"
#include "Camion_citerne.h"
#include <vector>
#include<iostream>

using namespace std;

class Livraison
{
private:
    Commande commande;
    Chauffeur * chauffeur; //aggregation
    Vehicule * vehicule;

public:
    Livraison() = default;
    Livraison(const Commande& commande, Chauffeur* chauffeur,Vehicule* vehicule) //on met un ptr pour avoir accès au bon vehicule
        : commande(commande), chauffeur(chauffeur), vehicule(vehicule) {}
    ~Livraison(){}

    void afficherInfos();
};

#endif