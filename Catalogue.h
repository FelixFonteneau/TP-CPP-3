/*************************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 17/12/2018
    copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
    e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées

#include <cstring>
#include "Trajet.h"
#include "CollectionTrajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include <string>
#include <fstream>

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>

// La classe catalogue a pour objectif de recenser l'ensemble des  trajets
// dans l'attribut : trajetsDisponibles,
// ainsi que de proposer des parcours pour deux paramètres donnés suivants
// - villeDepart : ville de départ du voyage demandé
// - villeFin : ville où se termine le voyage
// On peut enfin ajouter des trajets ainsi qu'afficher l'état du catalogue
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Menu();
    // Mode d'emploi : Affiche le menu principal qui permet d'intéragir avec le
    // catalogue à l'instant T, où la fonction est appellée
    // Contrat :

	void MenuSave();
	// Mode d'emploi : Affiche le menu permettant à l'utlisateur de choisir
	//quel type de sauvegarde ou chargement il veut appliquer à son catalogue
	// Contrat :

	void MenuSaveVille();
	// Mode d'emploi : Affiche un menu complémentaire au menuSave
	//qui permet à l'utilisateur de choisir dans le type de sauvegarde relatif au choix des villes
	//si son choix est par rapport à la ville d'arrivée de départ ou les deux.
	// Contrat :

    void Afficher() const;
    // Mode d'emploi : Nous affichons sur la sortie standard de manière ordonée le contenu du
    // catalogue à l'instant T, où la fonction est appellée
    // Contrat : Elle ne modifiera pas le contenu de l'instance catalogue

    void AjouterTrajet(const Trajet * t);
    // Mode d'emploi : Le trajet passé en paramètre, s'il est différent
    // de ceux déjà présents, sera ajouté au catalogue via un placement
    // au premier index libre via la méthode Ajouter de CollectionTrajet.
    // Contrat : Le trajet doit exister, bien entendu.
    //

    void RechercherParcoursSimple(const char *  vDep,
			    const char *  vFin) const;
    // Mode d'emploi : Nous récupérons dans la collection de trajets,
    // ceux qui possèdent une ville de départ ET une ville d'arrivée
    // égales aux paramètres, nous les affichons alors.
    // Contrat : vDep (et vFin) appartiennent à l'ensemble des villes
    // de départ (et fin, respectivement) dans le catalogue.

	bool SauvegardeAll(ofstream & fout,const char chemin[20]) const;
	//Mode d'emploi : Cette fonction permet d'enregistrer tous les trajets du catalogue 
	// dans le fichier dont le flux de sortie et le nom du fichier sont passés en paramètre. 
    // Contrat : Si l'acces au fichier est impossible, la fonction retournera
    // false.

	bool SauvegardeType(ofstream & fout, const char chemin[20], bool type) const;
	// Mode d'emploi : Cette fonction permet d'enregistrer tous les trajets du catalogue dont le type
    // dépend de la valeur de "bool type ": 0 --> un trajet simple et 1--> un trajet composé
    //dans le fichier dont le nom et le flux de sortie sont aussi passé en paramètre. 
    // La fonction renvoie false si aucun trajet n'a été ajouté au fichier et true sinon.
    // Contrat :Si l'acces au fichier est impossible, la fonction retournera
    // false

	bool SauvegardeVD(ofstream & fout, const char chemin[20], const char vd[20]) const;
	// Mode d'emploi:C ette fonction permet d'enregistrer tous les trajets du catalogue dont la ville 
	// de départ correspond au tableau de caractères passé en paramètre
	//dans le fichier dont le nom etle flux de sortie sont aussi passés en paramètre. 
	// La fonction renvoie false si aucun trajet n'a été ajouté au fichier et true sinon.
	// Contrat :Si l'acces au fichier est impossible, la fonction retournera
    // false.
	
	bool SauvegardeVA(ofstream & fout, const char chemin[20], const char va [20]) const;
	// Mode d'emploi: Cette fonction permet d'enregistrer tous les trajets du catalogue dont la ville 
    // d'arrivée correspond au tableau de caractères passé en paramètre
   //dans le fichier dont le nom et le flux de sortie sont aussi passés en paramètre. 
   // La fonction renvoie false si aucun trajet n'a été ajouté au fichier et true sinon.
   // Contrat :Si l'acces au fichier est impossible, la fonction retournera
   // false.

	bool SauvegardeVDA(ofstream & fout, const char chemin[20], const char vd[20],const char va [20]) const;
	// Mode d'emploi:C ette fonction permet d'enregistrer tous les trajets du catalogue dont la ville 
    // de départ et la ville d'arrivée correspondent aux tableau de caractères passés en paramètre
    //dans le fichier dont le nom etle flux de sortie sont aussi passés en paramètre. 
    // La fonction renvoie false si aucun trajet n'a été ajouté au fichier et true sinon.
    // Contrat :Si l'acces au fichier est impossible, la fonction retournera
    // false.

	bool SauvegardeSelec(ofstream & fout, const char chemin[20],unsigned const int n,const unsigned int m) const;
	// Mode d'emploi:Cette fonction permet d'enregistrer tous les trajets du catalogue contenu dans l'intervalle
	//qui a comme borne inférieur "n" et borne supérieur "m"
	//dans le fichier dont le nom etle flux de sortie sont aussi passés en paramètre. 
	// La fonction renvoie false si aucun trajet n'a été ajouté au fichier et true sinon.
	// Contrat :Si l'acces au fichier est impossible, la fonction retournera
	// false. La gestion de la validité de l'intervalle se fait dans le menu
	
	bool Chargement(std::string chemin);


//-------------------------------------------- Constructeurs - destructeur
	
    Catalogue ();
    // Mode d'emploi :
    // Constructeur de catalogue, prend un premier trajet en paramètre.
    // Contrat : Le trajet passé en paramètre est forcément existant.
    //

    virtual ~Catalogue ( );
    // Mode d'emploi :
    // Destructeur de catalogue.


//------------------------------------------------------------------ PRIVE

protected:
	TrajetSimple* creerTrajetSimple(std::ifstream &fichierEntree);
	// Mode d'emploi : Recupère les caractèristique d'un trajet simple
	// en prenant la ville de depart, d'arrivee et moyen de transport
	// étants sur le input stream et creer un nouveau trajet simple a partir
	// de ces caracterisiques sur le tas.
	// Contrat : Il faut qu'il y ai au moins trois mots sur le input stream

//----------------------------------------------------- Attributs protégés
    CollectionTrajet trajetsDisponibles;
};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H
