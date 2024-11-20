#include <iostream>
#include <string>
#include "Personne.h"
using namespace std;

class Salarie : public Personne    //salarie herite de la classe personne
{
private : 
	string numSS;
	string date_entree;
	string poste;
	double salaire;
public : 
	Salarie(string nom, string prenom,
		string adresse, string email, string telephone, string numeroSS,
		string date_entree, string poste, double salaire)
		: Personne(nom, prenom, adresse, email, telephone),
		numSS(numeroSS), date_entree(date_entree), poste(poste), salaire(salaire) {}
	
	string getNumeroSS() const { return numSS; }
	string getDateEntreeSociete() const { return date_entree; }
	string getPoste() const { return poste; }
	double getSalaire() const { return salaire; }

	void setNumeroSS(const string& numeroSS);
	void setDateEntreeSociete(const string& dateEntreeSociete);
	void setPoste(const string& poste);
	void setSalaire(double salaire);
	static vector<Salarie> OuvrirFichierSalarie();
	static void afficherListeSalarie();
	void afficherInfos() const override;
	static void ajouterSalarie();
	~Salarie(){}
};

