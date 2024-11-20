#ifndef CHAUFFEUR_H
#define CHAUFFEUR_H
#pragma once
#include <iostream>
#include <string>
#include "Personne.h"
#include "Commande.h"

using  namespace std;

class Chauffeur : public Personne
{
private:
	string numSS;
	bool dispo;

public:
	Chauffeur() : dispo(true){}
	Chauffeur(string &numSS, string &nom, string &prenom, string &adresse, string &email, string &telephone, bool disp) :Personne(nom, prenom, adresse, email, telephone), numSS(numSS), dispo(disp) {}
	bool getDispo() const;
	void setDispo(bool disponibilite);
	string getNumSS() const;
	static vector<Chauffeur> OuvrirFichierChauffeur();
	static vector<string> OuvrirFichierDates(string numSS);
	static void afficherListeChauffeur();
	static Chauffeur* Affectation(string date);
	void MettreAJour(string date);
	void afficherInfos() const override;
	static void ajouterChauffeur();
	static void ObtenirDispo(string numSS);
	static string obtenirDateDuJour();
	static void afficherDispo();
	~Chauffeur(){}
	
};

#endif

