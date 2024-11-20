
#include "Vehicule.h"
#include "Livraison.h"
#include "Chauffeur.h"
#include "Client.h"
#include "Trajet.h"
#include <vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<thread>
#include <iomanip> 
#include <algorithm>
#include <map>
#include "Commande.h"
#define BOLD   "\033[1m"
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"
#define COLOR   "\033[36m"

using namespace std;

Commande::Commande() : prix(0.0) {}

bool Commande::aCommande(const std::string& id, const std::vector<Commande>& listeCommandes) {
    for (const auto& commande : listeCommandes) {
        if (commande.getId() == id) {
            return true;
        }
    }
    return false;
}

void Commande::afficherInfosCommande(const Commande& commande){
    std::cout << "Id client: " << commande.getId() << std::endl;
    std::cout << "Ville de depart: " << commande.getDepart() << std::endl;
    std::cout << "Ville d'arrivee: " << commande.getArrivee() << std::endl;
    std::cout << "Prix: " << commande.getPrix() << " euros" << std::endl;
    std::cout << "Date: " << commande.getDate() << std::endl;
    std::cout << "Type: " << commande.getType() << std::endl;
}
void Commande::afficherListeCommandes(const std::vector<Commande>& listeCommandes) {
    std::cout <<BOLD<< "Liste des commandes : " <<RESET<<endl;
    for (const auto& commande : listeCommandes) {
        std::cout << "Identifiant Client : " << commande.getId() << std::endl;
        std::cout << "Depart : " << commande.getDepart() << std::endl;
        std::cout << "Arrivee : " << commande.getArrivee() << std::endl;
        std::cout << "Prix : " << commande.getPrix() << " euros"<<std::endl;
        std::cout << "Date : " << commande.getDate() << std::endl;
        std::cout << "Type : " << commande.getType() << std::endl;
        std::cout << std::endl;
    }
}
void Commande::afficherNombreCommandesParClient() {
    vector<Commande> commandes = Commande::OuvrirFichierCommande();
    map<std::string, int> nombreCommandesParClient; // conteneur associatif pour stocker le nombre de commandes par client
    
    // Compter le nombre de commandes pour chaque client
    for (const auto& commande : commandes) {
        nombreCommandesParClient[commande.getId()]++;
    }
    // Afficher le nombre de commandes pour chaque client
    std::cout << "Nombre de commandes par client : " << std::endl;
    for (const auto& paire : nombreCommandesParClient) {
        std::cout << "Client " << paire.first << " : " << paire.second << " commande(s)" << std::endl;
    }
}
void Commande::ajouterCommandeAuFichier(const Commande& nouvelleCommande, const std::string& nomFichier) {
    ofstream fichier(nomFichier,ios::app); // Ouvrir le fichier en mode d'ajout à la fin

    // Vérifier si le fichier est ouvert
    if (fichier.is_open()) {
        // Écrire les détails de la nouvelle commande dans le fichier
        fichier << nouvelleCommande.getId() << ","
            << nouvelleCommande.getDepart() << ","
            << nouvelleCommande.getArrivee() << ","
            << nouvelleCommande.getPrix() << ","
            << nouvelleCommande.getDate() << ","
            << nouvelleCommande.getType() << std::endl;

        // Fermer le fichier
        fichier.close();
        cout << "La commande a ete ajoutee avec succes au fichier." << std::endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier des commandes." << std::endl;
    }
}
vector<Commande> Commande::OuvrirFichierCommande() {
    ifstream fichier_commande("liste_commandes.txt");
    vector<Commande> Listecommandes;
    if (fichier_commande.is_open())
    {
        string ligne;
        if (getline(fichier_commande, ligne)) {
            do {
                std::stringstream ss(ligne);
                std::string id, depart, arrivee, date, type;
                double prix;

                // Extraire les données de la ligne
                std::getline(ss, id, ',');
                std::getline(ss, depart, ',');
                std::getline(ss, arrivee, ',');
                ss >> prix;
                ss.ignore();
                std::getline(ss, date, ',');
                std::getline(ss, type);

                // Créer une nouvelle commande et l'ajouter au vecteur commandes
                Listecommandes.emplace_back(id, depart, arrivee, prix, date, type);

            } while (std::getline(fichier_commande, ligne)); // Lire les lignes suivantes jusqu'à la fin du fichier 
        }
        else {
        // Le fichier est vide
        std::cout << "Aucune commande en cours.\n" << std::endl;
        }
        fichier_commande.close();        
    }
    return Listecommandes;
}
void Commande::PasserCommande(string idtf) {
    string dep, arr, date, type;
    double prix = 0.0;
    Vehicule* nouveauVehicule = nullptr;
    bool rep = false;
    std::cout << BOLD << "Type de produit :\n1) sable\n2) liquide\n3) marchandises perissables " << RESET << endl;
    int choix;
    cin >> choix;
    while (cin.fail() || choix != 1 && choix != 2 && choix != 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choix invalide. Veuillez entrer 1 ou 2" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
        cout << BOLD << "Type de produit :\n1) sable\n2) liquide\n3) marchandises perissables " << RESET << endl;
        cin >> choix;
    }
    system("CLS");
    // Vérifie le type de produit et crée le véhicule correspondant
    switch (choix)
    {
        case 1:
        {
            type = "sable";
            nouveauVehicule = Vehicule::Affectation(type);
        }
        break;
        case 2:
        {
            type = "liquide";
            nouveauVehicule = Vehicule::Affectation(type);
        }
        break;
        case 3:
        {
            type = "marchandises perissables";
            nouveauVehicule = Vehicule::Affectation(type);
        }
        break;
    }
    if (nouveauVehicule == nullptr) { delete nouveauVehicule; cout << "Aucun vehicule disponible. Commande annule." << endl; }
    else {
        std::cout << "Ville de depart : ";
        cin.ignore();
        getline(cin, dep);
        cout << "Ville d'arrivee : ";
        cin >> arr;
        cout << "Date de livraison : ";
        cin >> date;
        vector<Trajet> trajets = Trajet::lireTrajetsDepuisCSV();
        Trajet trajet = trouverTrajet(trajets, dep, arr);
        vector<Client> clients = Client::OuvrirFichierClient(); 
        for (auto& client : clients) {
            if (client.getId() == idtf) {
                if (trajet.depart != "") {
                    prix = trajet.calculerPrix();
                    if (client.getStatut() == "or") { prix = prix * 0.75; }  // 25% de reduction
                    if (client.getStatut() == "argent") { prix = prix * 0.9; } //10% de reduction
                }
                else {
                    prix = 35.0;
                }
                client.MAJmontant(idtf, prix);   // met à jour le statut du client (en fonction du prix)                            
            }
        }
        Commande nouvelleCommande(idtf, dep, arr, prix, date, type);

        Chauffeur* nouveauChauffeur;
        nouveauChauffeur = Chauffeur::Affectation(date);

        if (nouveauChauffeur == nullptr) { cout << "Aucun chauffeur disponible.Commande annule.\n" << endl; }
        else {
            Commande::ajouterCommandeAuFichier(nouvelleCommande, "liste_commandes.txt");

            Livraison nouvelleLivraison(nouvelleCommande, nouveauChauffeur, nouveauVehicule);
            system("CLS");
            nouvelleLivraison.afficherInfos();
        }
        delete nouveauVehicule;
    }
}

tm Commande::convertirDate(const std::string& date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%d/%m/%Y");
    if (ss.fail()) {
        throw std::runtime_error("Erreur lors de la conversion de la date.");
    }
    return tm;
}
void Commande::SupprimerCommandes() {
    std::vector<Commande> commandes = Commande::OuvrirFichierCommande();
    std::vector<Commande> commandesActuelles;

    std::time_t t = std::time(nullptr);
    std::tm maintenant = {};
    localtime_s(&maintenant, &t);

    for (const auto& commande : commandes) {
        std::tm dateLivraison = convertirDate(commande.getDate());
        if (std::difftime(std::mktime(&dateLivraison), std::mktime(&maintenant)) >= 0) {
            commandesActuelles.push_back(commande);
        }
        else {
            std::cout << "La commande du " << commande.getDate() << " a ete livree." << std::endl;
        }
    }

    std::ofstream fichier("liste_commandes.txt");
    for (const auto& commande : commandesActuelles) {
        fichier << commande.getId() << ","
            << commande.getDepart() << ","
            << commande.getArrivee() << ","
            << commande.getPrix() << ","
            << commande.getDate() << ","
            << commande.getType() << std::endl;
    }
    cout << endl;
}