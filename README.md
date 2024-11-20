# 🚚 Gestion des Livraisons TransConnect 🚚

## Description du projet
Ce projet est une application C++ développée pour gérer les opérations de la société de transport **TransConnect**. L’objectif est de fournir une solution permettant de :
- Gérer efficacement les salariés, les clients et les commandes. 
- Afficher la disponibilité des camions, chauffeurs en fonction de la date de livraison.
- Sauvegarder les données importantes pour créer une base auto-enrichissante.

## Fonctionnalités principales

### 🧑‍💻 Module Client
- Ajouter, modifier ou supprimer des clients.
- Afficher la liste des clients triée par :
  - Ordre alphabétique.
  - Ville.
  - Montant des achats cumulés (meilleurs clients).

### 🧑‍🔧 Module Salarié
- Ajouter ou licencier des salariés.
- Modifier les informations des salariés.
- Afficher leurs disponibilités.

### 🚛 Module Camion
- Assigner un camion à une commande en fonction du produit à livrer.
- Vérifier la disponibilité du véhicule avant assignation.
- Libérer automatiquement le camion après que la date de livraison soit passée. 

### 📦 Module Commande 
- Créer, modifier ou supprimer des commandes.
- Calculer le coût d’une commande en fonction de :
  - La distance parcourue.
  - Le tarif horaire du chauffeur (variable selon l’ancienneté).
- Optimiser le trajet d’une livraison avec l’algorithme de Dijkstra.
- Sauvegarder et afficher l’historique des commandes.

### 📊 Module Statistiques
- Nombre de livraisons effectuées par chauffeur.
- Commandes sur une période donnée.
- Moyenne des prix des commandes.
- Moyenne des montants des comptes clients.
- Liste des commandes par client.

## 🤖 Technologies utilisées
- **Langage** : C++
- **Environnement** : Visual Studio
- **Concepts C++ utilisés** :
  - Programmation orientée objet (POO) avec héritage.
  - Classes abstraites, polymorphisme, surcharge d'opérateurs et méthodes.
  - Pointeurs, passes par référence, destructeurs et constructeurs par copie.
  - Algorithmes STL : `sort`, `find_if`, `search`.
  - Utilisation d’au moins deux conteneurs STL différents avec itérateurs.

## Prérequis
- **Visual Studio** : Compiler et exécuter le projet.
- Connaissances de base en C++.

## Amusez vous bien ! ✨
