/*************************************************************************************
						  TrajetSimple-description
							 -------------------
	début                : 17/12/2018
	copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
	e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
char * TrajetSimple::EnvoyerVilleDepart() const
{
	return villeDepart;
}
char * TrajetSimple::EnvoyerVilleArrivee() const
{
	return villeArrivee;
}

char * TrajetSimple::EnvoyerMoyenDeTransport() const
{
	return moyenDeTransport;
}



void TrajetSimple::Afficher(void) const
// Algorithme :
//
{
	cout << "De " << villeDepart << " à " << villeArrivee << " en " <<
	moyenDeTransport;
}//----- Fin de Afficher





void TrajetSimple::Enregistrer(ofstream & fout) const
{ 
	fout <<" " << villeDepart << " " << villeArrivee << " " << moyenDeTransport ;
}//-----Fin Enregistrer

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple ( char * vDepart, char * vArrivee, char * mTransport)
// Algorithme : Les attributs sont déclarés dans le corps du constructeur 
// afin de pouvoir les détruire proprement à la destruction de l'objet, 
// ce qui s'avérait plus difficile avec la construction du type () : {} 
//
{

#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
	villeDepart = new char [20];
	villeArrivee = new char [20];
	moyenDeTransport = new char [20];
	strcpy(villeDepart,vDepart);
	strcpy(villeArrivee,vArrivee);
	strcpy(moyenDeTransport,mTransport);


} //----- Fin de TrajetSimple (constructeur de copie)


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
	delete [] villeDepart;
	delete [] villeArrivee;
	delete [] moyenDeTransport;
} //----- Fin de ~TrajetSimple


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
