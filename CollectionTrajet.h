/*************************************************************************************
						   CollectionTrajet  -  description
							 -------------------
	début                : 17/12/2018
	copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
	e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Interface de la classe <CollectionTrajet> (fichier CollectionTrajet.h) ----------------
#if ! defined ( COLLECTIONTRAJET_H )
#define COLLECTIONTRAJET_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include <fstream>

//------------------------------------------------------------------------
// Rôle de la classe <CollectionTrajet>
// Le rôle de la classe CollectionTrajet, comme son nom l'indique est de contenir 
// des objets hétérogènes dans une collection. En effet, nous avons fait le choix
// d'encapsuler la structure de données dans une classe afin de permettre la modification
// de l'implémentation de ce dernier sans pour autant modifier chacune des classes intervenantes.
// Ce choix s'apparente donc à de l'indépendance du système de sa structure de données,
// il ne fait que l'utiliser sans dépendre de son implémentation.
//------------------------------------------------------------------------

class CollectionTrajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Ajouter (const Trajet * tAjouter);
    // Mode d'emploi : Passage en paramètre d'un trajet, qui sera ajouté
    // à tous les trajets actuellement stockés dans la collection, s'il
    // ne s'agit pas d'un doublon bien entendu.
    // Contrat : Le trajet t ne sera pas modifié.
    //

    const Trajet & EnvoyerNiemeTrajet(const unsigned numTrajet) const ;
    // Mode d'emploi : Le trajet placé à la position i sera retourné
    // à l'appelant de cette méthode. Le trajet ainsi que la structure
    // de données contenant les trajets ne sera pas modifiée.
    // Contrat : La valeur numTrajet sera forcément inférieure ou
    // égale à la valeur de cardActuelle


    unsigned EnvoyerCard() const ;
    // Mode d'emploi : Simplement, la cardinalité de la structure de
    // données sera renvoyée.
    // Contrat : La cardinalité n'en est pas pour autant modifiée.
    //

//-------------------------------------------- Constructeurs - destructeur
    CollectionTrajet ( const CollectionTrajet & uneCollectionTrajet );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    CollectionTrajet ( unsigned cardinaliteMaximale = 2);
    // Mode d'emploi : Construit une structure de données de cardinalité
    // maximale 10 et initialise sa cardinalité actuelle à 0.
    //L'objet nécessite un premier trajet pour être initialisé
    // Contrat : L'objet créé est stable.
    //

    virtual ~CollectionTrajet ( );
    // Mode d'emploi :
    //
    // Contrat :
    //


protected:
//----------------------------------------------------- Attributs protégés
    const Trajet * * trajets ;
    unsigned cardMax;
    unsigned cardActuelle;
};

#endif // COLLECTIONTRAJET_H
