#include "Vehicule.h"
#include "Camion_benne.h"
#include "Camion_citerne.h"
#include "Camion_frigo.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#define BOLD   "\033[1m"
#define RESET   "\033[0m"

using namespace std;

bool Vehicule::getDispo() { return dispo; }
void Vehicule::setDispo(bool disp) { disp = dispo; }
vector<Vehicule*> Vehicule::OuvrirFichierVehicule() {
    ifstream fichier("liste_camions.txt");
    vector<Vehicule*> camions;

    string ligne;
    while (getline(fichier, ligne)) {
        istringstream ss(ligne);
        string type, plaque;
        bool dispo;

        // Séparation de la ligne en tokens en utilisant la virgule comme délimiteur
        getline(ss, type, ',');
        getline(ss, plaque, ',');
        ss >> boolalpha >> dispo; // Lecture du booléen avec des valeurs textuelles (true/false)

        // Création d'une instance appropriée de la classe de véhicule et mise à jour du compteur de disponibilité
        if (type == "camion_citerne") {
            Camion_citerne* camion = new Camion_citerne(plaque, dispo);
            Camion_citerne::ajouterCamionCiterne(camion);
            camions.push_back(camion);
        }
        else if (type == "camion_benne") {
            Camion_benne* camion = new Camion_benne(plaque, dispo);
            Camion_benne::ajouterCamionBenne(camion);
            camions.push_back(camion);
        }
        else if (type == "camion_frigo") {
            Camion_frigo* camion = new Camion_frigo(plaque, dispo);
            Camion_frigo::ajouterCamionFrigo(camion);
            camions.push_back(camion);
        }
    }

    fichier.close();
    return camions;
}
Vehicule* Vehicule::Affectation(const string& type) {
    Vehicule* nouveauVehicule = nullptr;
    vector<Vehicule*> vehiculesDisponibles = Vehicule::OuvrirFichierVehicule();
    for (Vehicule* vehicule : vehiculesDisponibles) {
        if (type == "sable") {                                                         
            if (Camion_benne* camionBenne = dynamic_cast<Camion_benne*>(vehicule)) {         //Regarde si le vehicule est un camion benne
                if (camionBenne->getDispo()) {
                    cout << "Camion benne : " << camionBenne->getPlaque() << endl;
                    nouveauVehicule = camionBenne;
                    camionBenne->MiseAJour();
                    break;
                }
            }
        }
        else if (type == "liquide") {
            if (Camion_citerne* camionCiterne= dynamic_cast<Camion_citerne*>(vehicule)) { //Regarde si le vehicule est un camion citerne
                if (camionCiterne->getDispo()) {
                    cout << "Camion citerne : " << camionCiterne->getPlaque() << endl;
                    nouveauVehicule = camionCiterne;
                    camionCiterne->MiseAJour();
                    break;
                }
            }
        }
        else {
            if (Camion_frigo* camionFrigo = dynamic_cast<Camion_frigo*>(vehicule)) {  //Regarde si le vehicule est un camion frigo
                if (camionFrigo->getDispo()) {
                    cout << "Camion frigo : " << camionFrigo->getPlaque() << endl;
                    nouveauVehicule = camionFrigo;
                    camionFrigo->MiseAJour();
                    break;
                }
            }
        }
        
    }
    return nouveauVehicule;
}
void Vehicule::afficherListeVehicule() {
    vector<Vehicule*> cam = Vehicule::OuvrirFichierVehicule();

    int nbCamionBenne = 0, nbCamionCiterne = 0, nbCamionFrigo = 0;
    cout << BOLD << "Liste des vehicules :" << RESET << endl;
    for (Vehicule* vehicule : cam) {
        vehicule->afficherInfos();
        if (dynamic_cast<Camion_benne*>(vehicule) && vehicule->getDispo() == true) { nbCamionBenne++; }
        else if (dynamic_cast<Camion_citerne*>(vehicule) && vehicule->getDispo() == true) { nbCamionCiterne++; }
        else if (dynamic_cast<Camion_frigo*>(vehicule) && vehicule->getDispo() == true) { nbCamionFrigo++; }
    }
    cout << "\nNombre de camions benne disponible : ";
    if (nbCamionBenne == 0) { cout << RED << nbCamionBenne << RESET; }
    else { cout << nbCamionBenne; }
    cout << "\nNombre de camions citerne disponible : ";
    if (nbCamionCiterne == 0) { cout << RED << nbCamionCiterne << RESET; }
    else { cout << nbCamionCiterne; }
    cout << "\nNombre de camions frigorifique disponible : ";
    if (nbCamionFrigo == 0) { cout << RED << nbCamionFrigo << RESET; }
    else { cout << nbCamionFrigo; }
    cout << endl<<endl;
}
       

