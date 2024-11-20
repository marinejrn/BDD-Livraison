#include "Trajet.h"
#include<string>
using namespace std;

void Trajet::AfficherlisteTrajet() 
{
    std::ifstream fichier("liste_trajets.txt");
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier liste_trajets.txt" << std::endl;
        return;
    }

    std::vector<Trajet> trajets;
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::istringstream ss(ligne);
        std::string depart, arrivee, temps;
        int distance;

        // Séparation de la ligne en tokens en utilisant la virgule comme délimiteur
        std::getline(ss, depart, ',');
        std::getline(ss, arrivee, ',');
        ss >> distance;
        ss.ignore();
        std::getline(ss, temps, ',');

        // Création d'un objet Trajet et ajout à la liste des trajets
        trajets.emplace_back(depart, arrivee, distance, temps);
    }

    // Fermeture du fichier
    fichier.close();

    // Affichage de la liste des trajets
    for (const auto& trajet : trajets) {
        std::cout << "Depart: " << trajet.depart << ", Arrivee: " << trajet.arrivee
            << ", Distance: " << trajet.distance << " km, Temps: " << trajet.temps << std::endl;
    }

}

vector<Trajet> Trajet::lireTrajetsDepuisCSV() {
    std::vector<Trajet> trajets;

    // Ouverture du fichier
    std::ifstream fichier("liste_trajets.txt");
    if (!fichier.is_open()) {
        // Gestion de l'erreur si le fichier ne peut pas être ouvert
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << "liste_trajets.txt" << std::endl;
        return trajets; // Retourne une liste de trajets vide
    }

    // Lecture du fichier ligne par ligne
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::istringstream iss(ligne);
        std::string dep, arr, tmp;
        int dist;

        // Extraction des données de la ligne
        if (std::getline(iss, dep, ',') &&
            std::getline(iss, arr, ',') &&
            iss >> dist &&
            std::getline(iss >> std::ws, tmp)) {
            // Création d'un nouvel objet Trajet et ajout à la liste
            trajets.emplace_back(dep, arr, dist, tmp);
            trajets.emplace_back(arr, dep, dist, tmp);
        }
        else {
            // Gestion de l'erreur si les données ne peuvent pas être extraites correctement
            std::cerr << "Erreur : Format de ligne invalide dans le fichier " << std::endl;
        }
    }

    // Fermeture du fichier
    fichier.close();

    return trajets;
}
Trajet trouverTrajet(const std::vector<Trajet>& trajets, const std::string& ville_depart, const std::string& ville_arrivee) {
    for (const auto& trajet : trajets) {
        if (trajet.depart == ville_depart && trajet.arrivee == ville_arrivee) {
            return trajet; // Retourner le premier trajet correspondant trouvé
        }
    }
    return Trajet("", "", 0, ""); // Retourner un trajet vide si aucun correspondant trouvé
}

double Trajet::calculerPrix() const {
    return 0.10* distance;    //0.10 choisit par l'entreprise
}