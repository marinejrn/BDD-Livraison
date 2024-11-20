#include "Chauffeur.h"
#include "Commande.h"
#include "Personne.h"
#include <fstream>
#include <iostream>
#include <string>
#include<sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <cctype>
#include <iomanip>
#define BOLD   "\033[1m"
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"
using namespace std;

bool Chauffeur::getDispo() const{ return dispo; }
void Chauffeur::setDispo(bool dispo) {dispo=dispo;}
string Chauffeur::getNumSS() const { return numSS; }

void Chauffeur::MettreAJour(string date_livraison) {
    fstream fichier("liste_dates.txt");

    vector<std::string> lignes;
    string ligne;
    while (getline(fichier, ligne)) {
        lignes.push_back(ligne);
    }
    for (string& l : lignes) {
        istringstream ss(l);
        string numSS;
        getline(ss, numSS, ','); // Le numéro de sécurité sociale est le premier champ

        // Vérifier si le numéro de sécurité sociale correspond à celui du chauffeur
        if (numSS == getNumSS()) {
            l += "," + date_livraison;
            break;
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
Chauffeur* Chauffeur::Affectation(string date_livraison) {
    vector<Chauffeur>listechauf = Chauffeur::OuvrirFichierChauffeur();
    Chauffeur* nouveauChauffeur=nullptr;
    for (auto& chauffeur : listechauf)
    {
        int compte = 0;
        vector<string> dates = OuvrirFichierDates(chauffeur.numSS);
        for(string date: dates){
            if (date == date_livraison) 
            {
                chauffeur.dispo = false;
            }
            compte++;
        }
        if (compte > 3) {
            chauffeur.dispo = false;
        }
    }
    for (auto& chauffeur : listechauf)
    {
        if (chauffeur.dispo == true) {
            nouveauChauffeur = new Chauffeur(chauffeur);
            chauffeur.MettreAJour(date_livraison);
            break;
        }
    }
    return nouveauChauffeur;
}

vector<string> Chauffeur::OuvrirFichierDates(string numSS)
{
    ifstream fichier_dates("liste_dates.txt");
    vector<string> dates;

    if (fichier_dates.is_open()) {
        string ligne;
        while (getline(fichier_dates, ligne)) {
            stringstream ss(ligne);
            string numSS_chauffeur, date;

            // Extraire les données de la ligne
            getline(ss, numSS_chauffeur, ',');
            if (numSS_chauffeur == numSS)
            {
                while (getline(ss, date, ','))
                {
                    dates.push_back(date);
                }
            }
        }
    }
    // Fermer le fichier
    fichier_dates.close();
    return dates;
}
vector<Chauffeur> Chauffeur::OuvrirFichierChauffeur() {
    ifstream fichier_chauffeur("liste_chauffeurs.txt");
    vector<Chauffeur> chauffeurs;

    if (fichier_chauffeur.is_open()) {
        string ligne;
        while (getline(fichier_chauffeur, ligne)) {
            stringstream ss(ligne);
            string numSS, nom, prenom, adresse, email, telephone, dispo;

            // Extraire les données de la ligne
            getline(ss, numSS, ',');
            getline(ss, nom, ',');
            getline(ss, prenom, ',');
            getline(ss, adresse, ',');
            getline(ss, email, ',');
            getline(ss, telephone, ',');
            getline(ss, dispo, ',');

            // Convertir la chaîne de disponibilité en booléen
            bool disponible = (dispo == "true");

            // Créer un nouvel objet Chauffeur et l'ajouter au vecteur chauffeurs
            chauffeurs.emplace_back(numSS, nom, prenom, adresse, email, telephone, disponible);
        }
    }
    // Fermer le fichier
    fichier_chauffeur.close();
    return chauffeurs;

}
string Chauffeur::obtenirDateDuJour() {
    // Obtenir le temps actuel
    std::time_t tempsActuel = std::time(nullptr);
    tm tmMaintenant;
    // Utilisation de localtime_s pour éviter les avertissements de sécurité
    localtime_s(&tmMaintenant, &tempsActuel);
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << tmMaintenant.tm_mday << "/"
        << std::setw(2) << (tmMaintenant.tm_mon + 1) << "/" << (tmMaintenant.tm_year + 1900);

    return ss.str();
}
void Chauffeur::ObtenirDispo(string numSS) {
    bool dispo = true;
    string date_du_jour = obtenirDateDuJour();
    vector<string>dates = OuvrirFichierDates(numSS);
    for (string date : dates) {
        if (date == date_du_jour) {
            dispo = false;
        }
    }
    if (dispo == true) {
        cout << GREEN << "disponible" << RESET << endl << endl;
    }
    else { cout << RED << "indisponible" << RESET << endl << endl; }
}
void Chauffeur::afficherDispo() {
    cout << BOLD << "Dates de livraison programmees : " << endl << RESET;
    vector<Chauffeur>chauffeurs = OuvrirFichierChauffeur();
    ifstream fichier_dates("liste_dates.txt");
    if (fichier_dates.is_open()) {
        string ligne;
        while (getline(fichier_dates, ligne)) {
            stringstream ss(ligne);
            string numSS_chauffeur, date;

            getline(ss, numSS_chauffeur, ','); // Lire le numéro de sécurité sociale

            for (Chauffeur& c : chauffeurs) {
                if (c.numSS == numSS_chauffeur) {
                    cout << BOLD << c.nom << " " << c.prenom << " : " << RESET;
                    while (getline(ss, date, ',')) {
                        cout << date << "   ";
                    }
                    cout << endl;
                    break; // Sortir de la boucle une fois le chauffeur trouvé
                }
            }
        }
        fichier_dates.close();
    }
    else {
        cout << "Impossible d'ouvrir le fichier des dates." << endl;
    }
    cout << endl;
}

void Chauffeur::afficherInfos() const 
{
    Personne::afficherInfos();
    cout << "Num SS : " << numSS << endl;
    cout << "Disponible : ";
    ObtenirDispo(numSS);  
}
void Chauffeur::ajouterChauffeur() {
    ofstream fichier("liste_chauffeurs.txt", ios::app);
    string nom, prenom, adresse, email, telephone, numSS;
    bool dispo;
        if (fichier.is_open()) {
            cout << BOLD << "Nom : " << RESET;
            cin >> nom;
            cout << BOLD << "Prenom : " << RESET;
            cin >> prenom;
            cout << BOLD << "Adresse : " << RESET;
            cin.ignore();
            getline(cin, adresse);
            cout << BOLD << "Email : " << RESET;
            cin >> email;
            cout << BOLD << "Telephone : " << RESET;
            cin >> telephone;
            cout << BOLD << "Numero de securite sociale : " << RESET;
            cin >> numSS;
            dispo = true;
            fichier << numSS<<","<<nom << "," << prenom << "," << adresse << "," << email << "," << telephone << "," << "true" << endl;
            Chauffeur new_chauf(nom, prenom, adresse, email, telephone, numSS, dispo);
            this_thread::sleep_for(chrono::seconds(1));
            system("CLS");

            cout << BOLD << "Recapitulatif des informations : " << RESET << endl;
            new_chauf.afficherInfos();
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
        }
        else {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt." << std::endl;
        }
        fichier.close();

        ofstream fichier_dates("liste_dates.txt", ios::app);
        if (fichier_dates.is_open()) {
            fichier_dates << numSS << ","<< endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("CLS");
        }
        else {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt." << std::endl;
        }
        fichier_dates.close();
}
void Chauffeur::afficherListeChauffeur() {
    vector<Chauffeur> liste = OuvrirFichierChauffeur();
    for (const auto& chauf : liste)
    {

        chauf.afficherInfos();
    }
}