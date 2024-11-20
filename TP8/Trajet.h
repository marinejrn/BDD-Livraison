#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Trajet
{
public:
    string depart;
    string arrivee;
    int distance;
    string temps;

    Trajet(const string& dep, const string& arr, int dist, const string& tmp)
        : depart(dep), arrivee(arr), distance(dist), temps(tmp) {}
    static void AfficherlisteTrajet();
    static vector<Trajet> lireTrajetsDepuisCSV();
    double calculerPrix() const;
};
Trajet trouverTrajet(const std::vector<Trajet>& trajets, const std::string& ville_depart, const std::string& ville_arrivee);


