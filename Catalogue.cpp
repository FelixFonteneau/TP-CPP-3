/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include <cstring>
#include <string>
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Catalogue::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Catalogue::Menu()
{
	char * villeDepartInit = new char[20];
	char * villeArriveeInit = new char[20];
	char * moyenDeTransportInit = new char[20];
	strcpy(villeDepartInit,"Lyon");
	strcpy(villeArriveeInit,"Avignon");
	strcpy(moyenDeTransportInit,"TGV");
	cout << "Bienvenue dans notre mini application de gestion de trajet ! \r\n"
	     << "Si vous souhaitez consulter la liste des commandes, tapez help." << endl;
	char * action = new char[50];
	TrajetSimple * trajetsSimples[50];
	const TrajetSimple * trajetsSimplesComposants[50];
	TrajetCompose * trajetsComposes[50];
	unsigned cptTrajetsSimples = 0;
	unsigned cptTrajetsComposes = 0;
	unsigned cptTrajetsSimplesComposants = 0;
	//TrajetSimple * trajetS = nullptr;
	//TrajetCompose * trajetC = nullptr;
	cin >> action;	
	while(strcmp(action,"quit") != 0){
		if(strcmp(action,"insert") == 0){
			cout<<"rentré insert" << endl;
			cin >> action;
			if(strcmp(action,"TS") == 0){
				cin >> action;
				strcpy(villeDepartInit,action);
				cin >> action;
				strcpy(villeArriveeInit,action);
				cin >> action;
				strcpy(moyenDeTransportInit,action);
				trajetsSimples[cptTrajetsSimples] = new TrajetSimple(villeDepartInit,villeArriveeInit,moyenDeTransportInit);
				AjouterTrajet(*trajetsSimples[cptTrajetsSimples]);
				cptTrajetsSimples++;
			}
			if(strcmp(action,"TC") == 0){
				cout << "rentré TC"<<endl;
				unsigned cptTrajet = 0;
				cin >> cptTrajet;
				for(unsigned i (0); i < cptTrajet; i++){	
					cin >> action;
					strcpy(villeDepartInit,action);
					cin >> action;
					strcpy(villeArriveeInit,action);
					cin >> action;
					strcpy(moyenDeTransportInit,action);
					trajetsSimplesComposants[cptTrajetsSimplesComposants] = new TrajetSimple(villeDepartInit,villeArriveeInit,moyenDeTransportInit);
					if(i==0){
						trajetsComposes[cptTrajetsComposes] = new TrajetCompose(*trajetsSimplesComposants[cptTrajetsSimplesComposants]);
					} else {
						trajetsComposes[cptTrajetsComposes]->Ajouter(*trajetsSimplesComposants[cptTrajetsSimplesComposants]);
					}
					cptTrajetsSimplesComposants++;
				}
				AjouterTrajet(*trajetsComposes[cptTrajetsComposes]);
				cptTrajetsComposes++;
			}
		}
		if(strcmp(action,"afficher") == 0){
			afficherFichier();
		}
		if(strcmp(action,"recherche") == 0){
			cin >> action;
			if(strcmp(action,"V1") == 0){
				cin >> action;
				strcpy(villeDepartInit,action);
				cin >> action;
				strcpy(villeArriveeInit,action);
				RechercherParcoursSimple(villeDepartInit,villeArriveeInit);
			}
		}
		if(strcmp(action,"help") == 0){
			cout << "Les commandes disponibles sont : \r\n"
			     << "Ajouter un trajet simple : insert TS <villeDepart> <villeArrivee> <moyenDeTransport> \r\n"
			     << "Ajouter un trajet composé : insert TC <n> [<villeDepart> <villeArrivee> <moyenDeTransport>] avec [] n>0 fois \r\n"
			     << "Afficher l'état actuel du catalogue : afficher \r\n"
			     << "Effectuer l'algorithme de recherche d'un trajet V1 : recherche V1 <villeDepart> <villeArrivee> \r\n"
			     << "Effectuer l'algorithme de recherche d'un trajet V2 : recherche V2 <villeDepart> <villeArrivee> \r\n"
			     << "--Fin de la liste des commandes disponibles-- \r\n";
		}
		cin >> action;
	}
	
	delete [] action;
	for(unsigned i(0); i<cptTrajetsSimples;i++){
		delete trajetsSimples[i];
	}
	for(unsigned i(0); i<cptTrajetsSimplesComposants;i++){
		delete trajetsSimplesComposants[i];
	}
	for(unsigned i(0); i<cptTrajetsComposes;i++){
		delete trajetsComposes[i];
	}
	delete [] villeDepartInit;	
	delete [] villeArriveeInit;	
	delete [] moyenDeTransportInit;	

}

void Catalogue::Afficher() const
{
  const int nbTrajets = trajetsDisponibles.EnvoyerCard();
  for (int i(0) ; i < nbTrajets; i++)
  {
    
    cout << i+1 << "  : ";
    const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
    iemeTrajet.Afficher();
    cout << '\n';
  }	
}

void Catalogue::afficherFichier() const
{
  const int nbTrajets = trajetsDisponibles.EnvoyerCard();
  for (int i(0) ; i < nbTrajets; i++)
  {
    const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
    string typeTrajet;
    if( iemeTrajet.EnvoyerType ())
    {
	typeTrajet = "TC";
    }
    else
    {
    	typeTrajet = "TS";
    }
    cout << typeTrajet << ":";
    iemeTrajet.AfficherFichier();
    cout << '\n';
  }
}

void Catalogue::AjouterTrajet(const Trajet & t)
{
  trajetsDisponibles.Ajouter(t);
}

void Catalogue::RechercherParcoursSimple(const char *  vDep, const char *  vFin) const
{
    cout << "Version simple :" << endl;
    const int nbTrajets = trajetsDisponibles.EnvoyerCard();
    int j = 1;
    for (int i(0) ; i < nbTrajets; i++)
    {
      const Trajet &iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
      if (strcmp(iemeTrajet.EnvoyerVilleDepart(),vDep) == 0 && strcmp(iemeTrajet.EnvoyerVilleArrivee(),vFin) == 0)
      {
        cout << j++ << "  : ";
        iemeTrajet.Afficher();
        cout << '\n';
      }
    }
}




//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue () : trajetsDisponibles()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
