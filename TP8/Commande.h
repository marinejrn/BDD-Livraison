#ifndef COMMANDE_H
#define COMMANDE_H
#include <ctime>
#include <iostream>
#include <string>
#include "Client.h"
#include "Chauffeur.h"
#include "Vehicule.h"
#include <iomanip> 
#include <algorithm>
using namespace std;


class Commande
{
private : 
	string id;
	string depart;
	string arrivee;
	double prix;
	string date;
    string type;
public : 
	Commande();
    Commande(string& id, 
        const string& depart, const string& arrivee, double prix, const string& date, const string &type)
        : id(id), depart(depart),
        arrivee(arrivee), prix(prix), date(date),type(type) {}

    //getter
    const string getId() const { return id; }
    const string& getDepart() const { return depart; }
    const string& getArrivee() const { return arrivee; }
    double getPrix() const { return prix; }
    const string& getDate() const { return date; }
    const string& getType() const { return type; }
    //setter
    void setClient(string id) { this->id = id; }
    void setDepart(const std::string& depart) { this->depart = depart; }
    void setArrivee(const std::string& arrivee) { this->arrivee = arrivee; }
    void setPrix(double prix) { this->prix = prix; }
    void setDate(const std::string& date) { this->date = date; }
    void setType(const std::string& type) { this->type = type; }

    static bool aCommande(const std::string& numSS, const vector<Commande>& listeCommandes);
    static void afficherListeCommandes(const vector<Commande>& listeCommandes);
    static vector<Commande> OuvrirFichierCommande();
    static void afficherNombreCommandesParClient();
    static void ajouterCommandeAuFichier(const Commande& nouvelleCommande, const string& nomFichier);
    static void afficherInfosCommande(const Commande& commande);
    static void PasserCommande(string idtf);
    static void SupprimerCommandes();
    static tm convertirDate(const std::string& date);

    ~Commande() {}
};
#endif  