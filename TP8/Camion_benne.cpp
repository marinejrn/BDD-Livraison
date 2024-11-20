#include "Camion_benne.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int Camion_benne::quantiteDispo = 0;

void Camion_benne::MiseAJour() {
    // Ouvrir le fichier en lecture et en écriture
    fstream fichier("liste_camions.txt");

    vector<std::string> lignes;
    string ligne;
    while (getline(fichier, ligne)) {
        lignes.push_back(ligne);
    }
    for (string& l : lignes) {
        istringstream ss(l);
        string vehiculeType, vehiculePlaque;
        bool vehiculeDispo;

        getline(ss, vehiculeType, ',');
        getline(ss, vehiculePlaque, ',');
        ss >> boolalpha >> vehiculeDispo; 

        // Vérifier si le type et la plaque correspondent à ceux du camion
        if (vehiculeType == "camion_benne" && vehiculePlaque == getPlaque()) {
            size_t pos = l.rfind(","); // 'rfind' commence par la fin pour trouver la dernière virgule dans la ligne
            if (pos != string::npos) {
                l.replace(pos + 1, 5,"false");
                break;
            }
        }
    }
    fichier.clear(); // Effacer le marqueur de fin de fichier
    fichier.seekp(0); // Placer le curseur au début du fichier
    for (const string& l : lignes) {
        fichier << l << std::endl;
    }

    // Fermer le fichier
    fichier.close();
}

