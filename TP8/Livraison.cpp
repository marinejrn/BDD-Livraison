#include "Livraison.h"
#include "Vehicule.h"
#include "Commande.h"
#define RESET   "\033[0m"
#define BOLD   "\033[1m"

void Livraison::afficherInfos()
{
    cout << BOLD<<"Informations sur la livraison :"<<RESET << endl;
    cout << "----------------------------------" << endl;
    cout <<BOLD<<"Commande :" <<RESET<< endl;
    Commande::afficherInfosCommande(commande);
    cout <<BOLD<< "\nChauffeur :" <<RESET<< endl;
    if (chauffeur == nullptr) { cout << "PROBLEME"; }
    else { chauffeur->afficherInfos(); }
    cout << BOLD << "\nVehicule :" << RESET << endl;            
    vehicule->afficherType();   // polymorphisme
    cout << "----------------------------------" << endl;
}


