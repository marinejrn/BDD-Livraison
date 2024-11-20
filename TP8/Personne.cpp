#include "Personne.h"
#include <iostream>

void Personne::afficherInfos() const {
    std::cout << "Nom: " << nom << std::endl;
    std::cout << "Prenom: " << prenom << std::endl;
    std::cout << "Adresse: " << adresse << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Telephone: " << telephone << std::endl;
}