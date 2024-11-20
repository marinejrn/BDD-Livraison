#include "Camion_frigo.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int Camion_frigo::quantiteDispo = 0;
void Camion_frigo::MiseAJour() {
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

        // S�paration de la ligne en tokens en utilisant la virgule comme d�limiteur
        getline(ss, vehiculeType, ',');
        getline(ss, vehiculePlaque, ',');
        ss >> boolalpha >> vehiculeDispo; // Lecture du bool�en avec des valeurs textuelles (true/false)

        // V�rifier si le type et la plaque correspondent � ceux du camion
        if (vehiculeType == "camion_frigo" && vehiculePlaque == getPlaque()) {
            size_t pos = l.rfind(","); // 'rfind' commence par la fin pour trouver la derni�re virgule dans la ligne
            if (pos != string::npos) {
                l.replace(pos + 1, 5, "false");
                break;
            }
        }
    }
    fichier.clear(); // Effacer le marqueur de fin de fichier
    fichier.seekp(0); // Placer le curseur au d�but du fichier
    for (const string& l : lignes) {
        fichier << l << std::endl;
    }

    // Fermer le fichier
    fichier.close();
}