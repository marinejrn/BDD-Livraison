#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <string>
#include <vector>
#include "Personne.h"
#include "Commande.h"
using namespace std;

class Client : public Personne    //Client herite de la classe personne
{
private : 
    string id;
    string numSS;
    string statut;
    double montantAchats;
public:
    Client(const string &id,string nom, string &prenom, string &adresse, string &email,string &telephone, string &numSS, string &statut,double montantAchats)
        : Personne(nom, prenom, adresse, email, telephone),id(id),numSS(numSS),statut(statut),montantAchats(montantAchats){}
    
    Client() = default;
    ~Client(){}
    string getStatut() const;
    void setMontantAchats(double montant);
    double getMontantAchats() const;
    string getId() const;

    void MAJmontant(string& id,double montant);

    void afficherInfos() const override; //polymorphisme
    static void trierClientsAlphabetique(std::vector<Client>& clients);   //appel par reference

    static vector<Client> OuvrirFichierClient();
    static void afficherListeClient(int affichage);
    static void CommandeEnCours(string& idtf);
    static void ajouterClient();
    static string RecupererId();
    static void supprimerClient(string& itdf);
    static bool ClientExistant(string& id);

    static Client trouverMeilleurClient();
    static Client trouverMeilleurClient_commandes();
};
#endif
