#include <iostream>
#include <string>
#include "Client.h"
#include "Salarie.h"
#include "Commande.h"
#include "Trajet.h"
#include "Vehicule.h"
#include "Camion_frigo.h"
#include "Camion_benne.h"
#include "Camion_citerne.h"
#include "Livraison.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <chrono>
#include <thread>

#define BOLD   "\033[1m"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define COLOR   "\033[36m"

using namespace std;

int main()
{
    /////////////////////////* DEBUT CODE *////////////////////////////
    vector<Client>listeclient = Client::OuvrirFichierClient();
    std::cout << BOLD << "[TRANSCONNECT]" << RESET << endl;
    std::cout << BOLD << "\n1. Espace Clients\n2. Espace Entreprise" << RESET << endl;
    int ch;
    std::cin >> ch;
    while (cin.fail() || ch != 1 && ch != 2) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choix invalide. Veuillez entrer 1 ou 2." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
        cout << BOLD << "[TRANSCONNECT]" << RESET << endl;
        cout << BOLD << "\n1. Espace Client\n2. Espace Entreprise" << RESET << endl;
        cin >> ch;
    }
    system("CLS");
    while (ch != 0)
    {
        switch (ch)
        {
        case 1:
        {
            cout << BOLD << "[ESPACE CLIENT]\n\n[1] Se Connecter\n[2] Nouveau Client" << RESET<<endl;
            int choix;
            cin >> choix;
            while (cin.fail() || choix != 1 && choix != 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choix invalide. Veuillez entrer 1 ou 2." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("CLS");
                cout << BOLD << "[ESPACE CLIENT]\n\n[1] Se Connecter\n[2] Nouveau Client" << RESET << endl;
                cin >> choix;
            }
            while (choix != 0)
            {
                if (choix == 2) { system("CLS"); Client::ajouterClient(); }
                cout << BOLD << "Entrer identifiant Client : " << RESET;
                string idtf;std::cin >> idtf;
                bool presence = Client::ClientExistant(idtf);
                if (presence == true) {
                    system("CLS");
                    std::cout << BOLD << "1.Passer une commande\n2.Commandes en cours\n3.Supprimer le compte" << RESET << endl;
                    std::cin >> ch;
                    while (cin.fail() || ch != 1 && ch != 2 && ch !=3) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Choix invalide. Veuillez entrer 1,2 ou 3." << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        system("CLS");
                        std::cout << BOLD << "1.Passer une commande\n2.Commandes en cours\n3.Supprimer le compte" << RESET << endl;
                        std::cin >> ch;
                    }
                    system("CLS");
                    if (ch == 3) {
                        cout << "Supression du compte en cours..." << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        Client::supprimerClient(idtf);
                        this_thread::sleep_for(chrono::seconds(2));
                        ch = 0;
                    }
                    while (ch != 0)
                    {
                        switch (ch)
                        {
                        case 1: {Commande::PasserCommande(idtf); }
                        break;
                        case 2:{Client::CommandeEnCours(idtf);}
                        break;
                        }
                        std::cout << BOLD << "1.Passer une commande\n2.Commandes en cours\n3.Supprimer le compte \n\n0.Se deconnecter" << RESET << endl;
                        std::cin >> ch;
                        while (cin.fail() || ch != 1 && ch != 2 && ch != 3 && ch!=0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Choix invalide. Veuillez entrer 1,2,3 ou 0." << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            system("CLS");
                            std::cout << BOLD << "1.Passer une commande\n2.Commandes en cours\n3.Supprimer le compte\n\n0.Se deconnecter" << RESET << endl;
                            std::cin >> ch;
                        }
                        system("CLS");
                    }
                    break;
                }
                else { cout << "Client non existant. Veuillez creer un compte." << endl; this_thread::sleep_for(chrono::seconds(2)); system("CLS"); }
                cout << BOLD << "[ESPACE CLIENT]\n\n[1] Se Connecter\n[2] Nouveau Client" << RESET << endl;
                cin >> choix;
                while (cin.fail() || choix != 1 && choix != 2) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Choix invalide. Veuillez entrer 1 ou 2." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    system("CLS");
                    cout << BOLD << "[ESPACE CLIENT]\n\n[1] Se Connecter\n[2] Nouveau Client" << RESET << endl;
                    cin >> choix;
                }
            }
            break;
        }
        case 2:
        {
            cout <<BOLD<< "[ESPACE ENTREPRISE]\n\n1.Commandes\n2.Salaries\n3.Clients\n4.Vehicules\n5.Statistiques\n\n0.Quitter" << RESET<<endl;
            cin >> ch;
            while (cin.fail() || ch != 1 && ch != 2 && ch != 3 && ch != 0 && ch!=4 &&ch!=5) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choix invalide. Veuillez entrer 1,2,3,4,5 ou 0." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("CLS");
                cout << BOLD << "[ESPACE ENTREPRISE]\n\n1.Commandes\n2.Salaries\n3.Clients\n4.Vehicules\n5.Statistiques\n\n0.Quitter" << RESET << endl;
                cin >> ch;
            }
            system("CLS");
            while (ch != 0)
            {
                switch (ch)
                {
                    case 1: // Commande en cours
                    {
                        Commande::SupprimerCommandes();
                        vector<Commande> listecommande= Commande::OuvrirFichierCommande();
                        Commande::afficherListeCommandes(listecommande);
                    }
                    break;
                    case 2: //Liste de Salariés
                    {
                        cout <<BOLD<< "[Salaries]\n1.Liste Employes\n2.Liste Chauffeurs" <<RESET<<endl;
                        int rep;
                        cin >> rep;
                        while (cin.fail() || rep != 1 && rep != 2) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Choix invalide. Veuillez entrer 1 ou 2" << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            system("CLS");
                            cout << BOLD << "[Salaries]\n1.Liste Employes\n2.Liste Chauffeurs" << RESET << endl;
                            cin >> rep;
                        }
                        switch (rep)
                        {
                        case 1:
                            system("CLS");
                            std::cout << BOLD << "[Employes : ]" << RESET << endl << endl;
                            Salarie::afficherListeSalarie();
                            cout << endl <<BOLD<< "[1] Ajouter Employe\n[0] Quitter"<<RESET << endl;
                            int ch;cin >> ch;
                            while (cin.fail() || ch != 1 && ch != 0) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Choix invalide. Veuillez entrer 1 ou 0" << endl;
                                this_thread::sleep_for(chrono::seconds(1));
                                system("CLS");
                                cout << endl << "[1] Ajouter Employe\n[0] Quitter" << endl;
                                cin >> ch;
                            }
                            system("CLS");
                            if (ch == 1) {Salarie::ajouterSalarie(); }
                            break;

                        case 2:
                            system("CLS");
                            std::cout << BOLD << "[Chauffeurs : ]" << RESET << endl << endl;
                            Chauffeur::afficherListeChauffeur();
                            cout << endl <<BOLD<< "[1] Afficher dates de livraison\n[2] Ajouter Chauffeur\n[0] Quitter"<<RESET<<endl;
                            ch;cin >> ch;
                            while (cin.fail() || ch != 1 && ch != 0 && ch!=2) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Choix invalide. Veuillez entrer 1,2 ou 0" << endl;
                                this_thread::sleep_for(chrono::seconds(1));
                                system("CLS");
                                cout << BOLD << "[Chauffeurs]" << endl << "[1] Afficher dates de livraison\n[2] Ajouter Chauffeur\n[0] Quitter" <<RESET<< endl;
                                cin >> ch;
                            }
                            system("CLS");
                            if (ch == 1) {Chauffeur::afficherDispo(); }
                            if(ch==2){Chauffeur::ajouterChauffeur();}
                            break;
                        }
                    }
                    break;
                    case 3: //Afficher les clients et leur nombre de commandes
                    {
                        cout <<BOLD<< "[Affichage]" << endl << "1.Par ordre alphabetique\n2.Par identifiant"<<RESET<<endl;
                        int affichage;
                        cin >> affichage;
                        while (cin.fail() || affichage != 1 && affichage != 2) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Choix invalide. Veuillez entrer 1 ou 2" << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            system("CLS");
                            cout <<BOLD << "[Affichage]" << endl <<  "1.Par ordre alphabetique\n2.Par identifiant" <<RESET<< endl;
                            cin >> ch;
                        }
                        cout <<BOLD<< "[Liste Clients]" <<RESET<< endl<<endl;
                        Client::afficherListeClient(affichage);
                        Commande::afficherNombreCommandesParClient();
                        std::cout << endl;
                    }
                    break;
                    case 4: //Liste Vehicules et le nombre de chaque
                    {  Vehicule::afficherListeVehicule();}
                    break;
                    case 5:
                    {

                        cout <<BOLD<< "[Statistiques]\n\n1.Meilleur client par montant\n2.Meilleur client par nombre de commandes"<<RESET<<endl;
                        cin >> ch;
                        while (cin.fail() || ch != 1 && ch != 2) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Choix invalide. Veuillez entrer 1,2 ou 3" << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            system("CLS");
                            cout << BOLD << "[Statistiques]\n\n1.Meilleur client par montant\n2.Meilleur client par nombre de commandes" << RESET << endl;
                            cin >> ch;
                        }
                        switch (ch) {
                        case 1:
                        {
                            system("CLS");
                            Client meilleurClient = Client::trouverMeilleurClient();
                            cout << "Le meilleur client est : " << meilleurClient.getNom() << " " << meilleurClient.getPrenom() << " avec un montant d'achats de " << meilleurClient.getMontantAchats() << " euros." << endl << endl;
                            break;
                        }
                        case 2:
                        {
                            Client meilleurClient = Client::trouverMeilleurClient_commandes();
                            std::cout << "Le meilleur client est : " << meilleurClient.getNom() << " " << meilleurClient.getPrenom() << endl << endl;
                            break;
                        }
                        }

                    }
                    case 0:
                        break;
                }
                std::cout << BOLD << "[ESPACE ENTREPRISE]\n\n1.Commandes\n2.Salaries\n3.Clients\n4.Vehicules\n5.Statistiques\n\n0.Quitter" << RESET << endl;
                std::cin >> ch;
                while (cin.fail() || ch != 1 && ch != 2 && ch != 3 && ch != 0 && ch != 4 && ch!=5) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Choix invalide. Veuillez entrer 1,2,3,4,5 ou 0." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    system("CLS");
                    cout << BOLD << "[ESPACE ENTREPRISE]\n\n1.Commandes\n2.Salaries\n3.Clients\n4.Vehicules\n5.Statistiques\n\n0.Quitter" << RESET << endl;
                    cin >> ch;
                }
                system("CLS");
            }
        }
        break;
            case 0:
                break;
        }
        system("CLS");
        std::cout <<BOLD<< "[TRANSCONNECT]" << endl<< "1. Espace Clients\n2. Espace Entreprise\n\n0. Quitter" <<RESET<< endl;  std::cin >> ch;
        while (cin.fail() || ch != 1 && ch != 2 && ch!=0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choix invalide. Veuillez entrer 1,2 ou 0." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("CLS");
            cout << BOLD << "[TRANSCONNECT]" << RESET << endl;
            cout << BOLD << "\n1. Espace Clients\n2. Espace Entreprise \n\n0. Quitter" << RESET << endl;
            cin >> ch;
        }
        system("CLS");
    }
}
