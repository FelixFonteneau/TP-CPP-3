/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

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

    virtual void AfficherFichier () const = 0;
    //mode d'emploi : Affiche le trajet pour la sauvegarde
    //dans la sortie standard.

    virtual bool EnvoyerType () const = 0;
    //mode d'emploi : Envoi un bool pour savoir le type du fichier
    //envoi 0 pour un trajet simple et 1 pour trajet compose.


    virtual char * EnvoyerVilleDepart() const = 0;

    virtual char * EnvoyerVilleArrivee() const = 0;

    virtual ~Trajet(){}
    //les accolades sont obligatoires, sinon erreur de reference indefinie
    // a l'edition des liens.


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
   char * villeDepart;
   char * villeArrivee;

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // TRAJET_H
