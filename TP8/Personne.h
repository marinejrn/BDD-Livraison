#ifndef PERSONNE_H
#define PERSONNE_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Personne
{
protected : 
	string nom;
	string prenom;
	string adresse;
	string email;
	string telephone;
public : 
	Personne(string &nom, string &prenom, string &adresse, string &email, string &telephone)
		: nom(nom), prenom(prenom), adresse(adresse), email(email), telephone(telephone) {}
	Personne() = default;

	string getNom() const { return nom; }
	string getPrenom() const { return prenom; }
	string getAdresse() const { return adresse; }
	string getEmail() const { return email; }
	string getTelephone() const { return telephone; }
	virtual void afficherInfos() const;
	virtual ~Personne(){}
};

#endif

