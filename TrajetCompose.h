/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "CollectionTrajet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

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

   virtual void AfficherFichier () const;
   //mode d'emploi : Affiche le trajet Compose pour la sauvegarde  
   //dans la sortie standard.



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

  bool Ajouter(const Trajet & t);
  // Mode d'emploi : Ajoute un trajet t au trajet composé, mais verifie avant
  // que les départ correspond à l'arrivée ddu trajet actuel.
  // retourne un bool si le trajet a été ajouté ou non.
  // Contrat :
  //



//------------------------------------------------- Surcharge d'opérateurs
    //TrajetCompose & operator = ( const TrajetCompose & unTrajetCompose );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose (const Trajet & t);
    // Mode d'emploi : Construit un trajet composé à partir d'un Trajet
    // peu importe qu'il soit simple ou composé
    // Contrat : Le Trajet doit exister bien entendu.

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  CollectionTrajet trajetsComposants;
};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TrajetCompose_H
