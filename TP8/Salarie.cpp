#include "Salarie.h"
#include "Personne.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <thread>

#define BOLD   "\033[1m"
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"
#define COLOR   "\033[36m"

using namespace std;

void Salarie::setNumeroSS(const string& numeroSS) { this->numSS = numeroSS; }
void Salarie::setDateEntreeSociete(const string& dateEntreeSociete) { this->date_entree = dateEntreeSociete; }
void Salarie::setPoste(const string& poste) { this->poste = poste; }
void Salarie::setSalaire(double salaire) { this->salaire = salaire; }

vector<Salarie> Salarie::OuvrirFichierSalarie() {
    ifstream fichier_salaries("liste_salaries.txt");
    vector<Salarie> salaries;

    if (fichier_salaries.is_open())
    {
        std::string ligne;
        while (getline(fichier_salaries, ligne))
        {
            std::stringstream ss(ligne);
            std::string nom, prenom, adresse, email, telephone, numSS, poste,date_entree;
            double salaire;

            // Extraire les données de la ligne
            std::getline(ss, nom, ',');
            std::getline(ss, prenom, ',');
            std::getline(ss, adresse, ',');
            std::getline(ss, email, ',');
            std::getline(ss, telephone, ',');
            std::getline(ss, numSS, ',');
            std::getline(ss, date_entree, ',');
            std::getline(ss, poste, ',');           
            ss >> salaire;

            // Créer un nouvel objet Client et l'ajouter au vecteur clients
            salaries.emplace_back(nom, prenom, adresse, email, telephone, numSS, date_entree,poste, salaire);
        }
    }
    else
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt." << std::endl;
    }
    fichier_salaries.close();
    return salaries;
}
void Salarie::afficherListeSalarie() {
    vector<Salarie> liste = OuvrirFichierSalarie();
    for (auto const& salarie : liste) {
        salarie.afficherInfos();
        cout << endl;
    }
}
void Salarie::afficherInfos()const {
    cout<<BOLD << "Poste: " << poste <<RESET<< endl;
    Personne::afficherInfos();
    cout << "Num SS: " << numSS << endl;
    cout << "Salaire: " << salaire << endl;
}
void Salarie::ajouterSalarie() {
    ofstream fichier("liste_salaries.txt",ios::app);
    string nom, prenom, adresse, email, telephone, numSS, date_entree, poste;
    double salaire;
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
        cout << BOLD << "Date d'entree (00/00/0000) : " << RESET;
        cin >> date_entree;
        cout << BOLD << "Poste : " << RESET;
        cin >> poste;
        cout << BOLD << "Salaire : " << RESET;
        cin >> salaire;
        fichier << nom << "," << prenom << "," << adresse << "," << email << "," << telephone << "," << numSS << "," << date_entree <<","<< poste << "," << salaire << endl;
        Salarie new_sal(nom, prenom, adresse, email, telephone, numSS, date_entree, poste, salaire);
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");

        cout << BOLD << "Recapitulatif des informations : " << RESET << endl;
        new_sal.afficherInfos();
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
    }
    else {
      std::cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt." << std::endl;
    }
    fichier.close();
}
