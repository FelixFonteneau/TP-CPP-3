/*************************************************************************************
						 TrajetCompose  -  description
							 -------------------
	début                : 17/12/2018
	copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
	e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TrajetSimple.h"
#include "CollectionTrajet.h"
#include <fstream>

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
// Un trajet composé hérite des caractéristiques de la classe Trajet,
// mais en se distinguant d'un trajet simple de sa composition.
// En effet, un trajet composé va etre composé de trajets simples et/ou de trajets composés.
// Il y aura donc une succession de trajets qui sont relié par des villes dites étapes
// (pour chaque ville de fin de trajet composant différent de la ville d'arrivée, il existe une même ville de départ de trajet composant).
// Ceci explique la liste de trajets du type CollectionTrajet.


//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


  virtual bool EnvoyerType () const
  {
      return 1;
  }
    //mode d'emploi : Envoi un bool pour savoir le type du fichier
    //envoi 0 pour un trajet simple et 1 pour trajet compose.
    //en locurence envera 1 ici


  virtual void Afficher () const;
  // Mode d'emploi : Affiche sur la sortie standard le déroulement du trajet
  // composé, c'est à dire le départ, les étapes, l'arrivée et les différents
  // moyens de transports entre.
  // Contrat :
  //

  virtual char * EnvoyerVilleDepart() const;
  // Mode d'emploi :
  // Renvoie la ville de départ, on effectue pas de passage par références
  // car un char [20], n'est pas trop lourd.
  // Contrat :
  //

  virtual char * EnvoyerVilleArrivee() const;
  // Mode d'emploi :
  // Renvoie la ville d'arrivée, on effectue pas de passage par références
  // car un char [20], n'est pas trop lourd.
  // Contrat :

  bool Ajouter(const Trajet * t);
  // Mode d'emploi : Ajoute un trajet t au trajet composé, mais verifie avant
  // que les départ correspond à l'arrivée ddu trajet actuel.
  // retourne un bool si le trajet a été ajouté ou non.
  // Contrat :
  //

  virtual void Enregistrer(ofstream & fout) const;
  // Mode d'emploi : Renvoie dans le fichier dont le flux de sortie est passé en paramètre
	//le trajet composé avec un affichage spécial fichier


//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose (const Trajet * t);
    // Mode d'emploi : Construit un trajet composé à partir d'un Trajet
    // peu importe qu'il soit simple ou composé
    // Contrat : Le Trajet doit exister bien entendu.

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

protected:
//----------------------------------------------------- Attributs protégés
  CollectionTrajet trajetsComposants;
};

#endif // TrajetCompose_H
