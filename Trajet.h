/*************************************************************************************
						   Trajet  -  description
							 -------------------
	début                : 17/12/2018
	copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
	e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H
using namespace std;
//--------------------------------------------------- Interfaces utilisées
#include <fstream>

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>

// La classe abstraite Trajet a pour rôle d'assurer l'homogéinité des traitements
// possibles sur les objets qui en héritent. En effet, chacun d'entre eux doit 
// assurer sa capacité à s'afficher, renvoyer sa ville de départ et d'arrivée.
// Comme nous nous situons dans le cadre d'une classe abstraite, les méthodes sont 
// virtuelles pures et aucun constructeur n'est proposé.
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    virtual void Afficher () const = 0;

   // virtual void AfficherFichier () const = 0;
    //mode d'emploi : Affiche le trajet pour la sauvegarde  
    //dans la sortie standard.

    virtual bool EnvoyerType () const = 0;
    //mode d'emploi : Envoi un bool pour savoir le type du fichier
    //envoi 0 pour un trajet simple et 1 pour trajet compose.

    virtual char * EnvoyerVilleDepart() const = 0;
	//mode d'emploi : Envoie la ville de depart du trajet

    virtual char * EnvoyerVilleArrivee() const = 0;
	//mode d'emploi : Envoie la ville d'arrivee du trajet

	virtual void Enregistrer(ofstream & fout) const = 0;
	// Mode d'emploi : Renvoie dans le fichier dont le flux de sortie est passé en paramètre
	//le trajet avec un affichage spécial fichier

	virtual ~Trajet() {}
	//Destructeur de Trajet

protected:
//----------------------------------------------------- Attributs protégés
   char * villeDepart;
   char * villeArrivee;

};

#endif // TRAJET_H
