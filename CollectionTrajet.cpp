/*************************************************************************************
						   CollectionTrajet  -  description
							 -------------------
	début                : 17/12/2018
	copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
	e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Réalisation de la classe <CollectionTrajet> (fichier CollectionTrajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "CollectionTrajet.h"
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void CollectionTrajet::Ajouter (const Trajet * tAjouter)
{
	if (cardActuelle == cardMax) {
#ifdef MAP
		cout << "Elargissement de la structure de donnée" << endl;
#endif
		//nouvelle allocation d'un espace plus grand
		const Trajet * * nouveauxTrajets = new const Trajet *[cardMax + 5];
		//début copie
		for (unsigned i(0); i < cardMax; i++) {
			nouveauxTrajets[i] = trajets[i];
		} // fin copie
		//rendre l'espace précedemment alloué
		delete[] trajets;
		trajets = nouveauxTrajets;
		cardMax += 5;
	}
	trajets[cardActuelle] = tAjouter;
	++cardActuelle;
} //----- Fin de Ajouter

unsigned CollectionTrajet::EnvoyerCard () const
// Algorithme : Renvoie simplement la valeur de l'attribut CardActuelle;
{
	return cardActuelle;
} //----- Fin de EnvoyerCard

const Trajet & CollectionTrajet::EnvoyerNiemeTrajet(const unsigned numTrajet) const
// Algorithme : Renvoie simplement par référence le trajet numéro i
// après vérification de la valeur;
{
		return  *trajets[numTrajet];
} //--------Fin de EnvoyerNiemeTrajet

//-------------------------------------------- Constructeurs - destructeur
CollectionTrajet::CollectionTrajet ( const CollectionTrajet & uneCollectionTrajet )
// Algorithme :
//
:	trajets (nullptr),
cardMax(uneCollectionTrajet.cardMax),
cardActuelle(uneCollectionTrajet.cardActuelle)

{
	trajets = uneCollectionTrajet.trajets;
#ifdef MAP
    cout << "Appel au constructeur de copie de <CollectionTrajet>" << endl;
#endif
} //----- Fin de CollectionTrajet (constructeur de copie)


CollectionTrajet::CollectionTrajet ( unsigned cardinaliteMaximale)
: 	trajets (nullptr),
	cardMax (cardinaliteMaximale),
	cardActuelle (0)
// Algorithme :
//
{
	#ifdef MAP
	    cout << "Appel au constructeur de <CollectionTrajet>" << endl;
	#endif
	trajets = new const Trajet * [cardMax];

} //----- Fin de CollectionTrajet


CollectionTrajet::~CollectionTrajet ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <CollectionTrajet>" << endl;
#endif
	for (unsigned i(0); i < cardActuelle; i++) {
		delete trajets[i];
}
	delete[] trajets;


} //----- Fin de ~CollectionTrajet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
