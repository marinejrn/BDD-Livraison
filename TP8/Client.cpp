#include "Client.h"
#include "Commande.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <thread>
#include <map>
#include <stdexcept>
#define BOLD   "\033[1m"
#define RESET   "\033[0m" 
#define OCRE   "\033[33m" 
#define BLEU   "\033[36m" 
using namespace std;


void Client::setMontantAchats(double montant) {
    montantAchats = montant;
}
double Client::getMontantAchats() const {
    return montantAchats;
}
string Client::getId()const { return id; }
string Client::getStatut()const { return statut; }

void Client::afficherInfos() const {
    cout << "Identifiant Client :" << id << endl;
    Personne::afficherInfos();
    cout << "Num SS :" << numSS<<endl;
    cout << "Statut :";
    if (statut == "bronze") { cout <<" bronze" <<endl; }
    if (statut == "argent") { cout <<BLEU<< " argent" <<RESET<< endl; }
    if (statut == "or") { cout << OCRE << " or" << RESET << endl; }
    cout << "Montant des achats cumules : " << montantAchats << endl;
}
vector<Client> Client::OuvrirFichierClient(){
    ifstream fichier_clients("liste_clients.txt");
    vector<Client> clients;

    if (fichier_clients.is_open())
    {
        std::string ligne;
        while (std::getline(fichier_clients, ligne))
        {
            std::stringstream ss(ligne);
            std::string id, nom, prenom, adresse, email, telephone, numSS, statut;
            double montantAchats;

            // Extraire les données de la ligne
            std::getline(ss, id, ',');
            std::getline(ss, nom, ',');
            std::getline(ss, prenom, ',');
            std::getline(ss, adresse, ',');
            std::getline(ss, email, ',');
            std::getline(ss, telephone, ',');
            std::getline(ss, numSS, ',');
            std::getline(ss, statut, ',');
            ss >> montantAchats;

            // Créer un nouvel objet Client et l'ajouter au vecteur clients
            clients.emplace_back(id, nom, prenom, adresse, email, telephone, numSS, statut, montantAchats);
        }
    }
    else
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt." << std::endl;
    }
    fichier_clients.close();
    return clients;
}

void Client::afficherListeClient(int affichage) {
    vector<Client> listeclients = Client::OuvrirFichierClient();
    system("CLS");
    if(affichage==1){ trierClientsAlphabetique(listeclients); } 
    for (auto const& client : listeclients) {
        client.afficherInfos();
        std::cout << endl;
    }        
}
void Client::trierClientsAlphabetique(vector<Client>& clients) {
    sort(clients.begin(), clients.end(), [](const Client& a, const Client& b) {
        return a.getNom() < b.getNom();
        });
}
void Client::MAJmontant(string& idClient, double nouveauMontant) {
    std::fstream fichier("liste_clients.txt");
    std::vector<std::string> lignes;
    std::string ligne;
    while (std::getline(fichier, ligne)) {
        lignes.push_back(ligne);
    }

    // Parcourir les lignes pour trouver et mettre à jour le montant total des achats du client
    for (std::string& l : lignes) {
        // Identifier la ligne correspondant au client en utilisant son identifiant
        size_t pos = l.find(",");
        if (pos != std::string::npos) {
            std::string idClientCourant = l.substr(0, pos);
            if (idClientCourant == idClient) {

                size_t posMontant = l.find_last_of(",");
                std::string montantStr = l.substr(posMontant + 1);
                double montant = std::stod(montantStr);
                if(montant>=150){
                    montant += nouveauMontant;
                    l.replace(posMontant + 1, montantStr.length(), to_string(montant));
                }
                else {
                    montant += nouveauMontant;
                    l.replace(posMontant + 1, montantStr.length(), to_string(montant));

                    string statut = "bronze";
                    if (montant >= 50) {
                        statut = "argent";
                    }
                    if (montant >= 150) {
                        statut = "or";
                    }
                    size_t posStatut = l.find_last_of(",");
                    l.replace(posStatut - 6, 6, statut);
                }              
                break;
                
            }
        }
    }
    fichier.close();
    fichier.open("liste_clients.txt", std::ios::out | std::ios::trunc);

    for (const std::string& l : lignes) {
        fichier << l << std::endl;
    }

    fichier.close();
}
void Client::CommandeEnCours(string& idtf) {
    vector<Commande> commandeClient = Commande::OuvrirFichierCommande();
    int nb = 1;
    for (auto& comm : commandeClient) {
        if (comm.getId() == idtf) {
            cout << "Commande " << nb << endl;
            Commande::afficherInfosCommande(comm);
            cout << endl;
            nb++;
        }
    }
    if (nb == 1) { cout << "Aucune commande en cours." << endl; }
}
string Client::RecupererId() {
    vector<Client>listeclient = Client::OuvrirFichierClient();
    const Client& dernierClient = listeclient.back();
    int nb_id= stoi(dernierClient.getId());
    nb_id++;
    string new_id;
    if (nb_id < 10) {
        new_id = "00" + to_string(nb_id);
    }
    else
    {
        new_id = "0" + to_string(nb_id);
    }
    return new_id;
}
void Client::ajouterClient() {
    ofstream fichier("liste_clients.txt", ios::app);
    cout <<BOLD<< "[Nouveau Client]"<<RESET<<endl;
    string iD, nom, prenom, adresse, email, telephone, numSS,statut;
    if (fichier.is_open()) {
        cout <<BOLD<< "Nom : "<<RESET;
        cin>>nom;
        cout <<BOLD<< "Prenom : "<<RESET;
        cin >> prenom;
        cout <<BOLD<< "Adresse : "<<RESET;
        cin.ignore();
        getline(cin, adresse);
        cout <<BOLD<< "Email : "<<RESET;
        cin >> email;
        cout <<BOLD<< "Telephone : "<<RESET;
        cin >> telephone;
        cout <<BOLD<< "Numero de securite sociale : "<<RESET;
        cin >> numSS;
        iD = Client::RecupererId();
        statut = "bronze";
        fichier <<iD << "," << nom << "," << prenom << "," << adresse << "," << email << "," << telephone << "," << numSS << "," << statut << "," << 0 << endl;
        Client new_client(iD, nom, prenom, adresse, email, telephone, numSS,statut,0.0);
        cout << BOLD << "Votre numero d'identifiant : " << BLEU << iD << RESET << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");

        cout <<BOLD<<"Recapitulatif des informations : " <<RESET<< endl;
        new_client.afficherInfos();
        cout << "\nCompte Client en cours de validation. Veuillez patienter." << endl;       
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        cout << "Compte Client valide. Veuillez vous identifier." << endl;       
    }
    else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt." << std::endl;
    }
    fichier.close();
}
bool Client::ClientExistant(string& id) {
    bool presence = false;
    vector<Client> listeclient = OuvrirFichierClient();
    for (Client c : listeclient) {
        if (c.getId() == id) { presence = true; }
    }
    return presence;
}
void Client::supprimerClient(string& identifiant) {
    ifstream fichier("liste_clients.txt");
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier liste_clients.txt." << endl;
        return;
    }

    // Créer un fichier temporaire pour stocker les clients sans celui à supprimer
    ofstream fichierTemporaire("temp.txt");
    if (!fichierTemporaire.is_open()) {
        cerr << "Erreur : Impossible de créer le fichier temporaire." << endl;
        fichier.close();
        return;
    }

    string ligne;
    bool clientTrouve = false;
    while (getline(fichier, ligne)) {
        if (!ligne.empty()) {
            istringstream iss(ligne);
            string idClient;
            getline(iss, idClient, ','); // Lire l'identifiant jusqu'à la virgule
            if (idClient == identifiant) {
                // Le client à supprimer a été trouvé
                clientTrouve = true;
            }
            else {
                // Écrire cette ligne dans le fichier temporaire
                fichierTemporaire << ligne <<endl;
            }
        }
    }
    fichier.close();
    fichierTemporaire.close();

    // Supprimer le fichier original
    remove("liste_clients.txt");

    // Renommer le fichier temporaire pour remplacer le fichier original
    if (rename("temp.txt", "liste_clients.txt") != 0) {
        cerr << "Erreur : Impossible de renommer le fichier temporaire." << endl;
    }
    else {
        cout << "Le client avec l'identifiant " << identifiant << " a ete supprime." << endl;
    }

}

Client Client::trouverMeilleurClient() {
    vector<Client> clients = Client::OuvrirFichierClient();
    if (clients.empty()) {
        throw runtime_error("La liste des clients est vide.");
    }
    const Client* meilleurClient = &clients[0];
    for (const auto& client : clients) {
        if (client.montantAchats > meilleurClient->montantAchats) {
            meilleurClient = &client;
        }
    }
    return *meilleurClient;
}

Client Client::trouverMeilleurClient_commandes() {
    vector<Client> clients = Client::OuvrirFichierClient();
    vector<Commande> commandes = Commande::OuvrirFichierCommande();

    std::map<std::string, int> nombreCommandesParClient;

    for (const auto& commande : commandes) {
        nombreCommandesParClient[commande.getId()]++;
    }
    const Client* meilleurClient=nullptr;
    int maxCommandes = 0;

    for (const auto& client : clients) {
        auto it = nombreCommandesParClient.find(client.id);
        if (it != nombreCommandesParClient.end() && it->second > maxCommandes) {
            maxCommandes = it->second;
            meilleurClient = &client;
        }
    }
    return *meilleurClient;
}

