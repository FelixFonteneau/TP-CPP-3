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
#include <fstream>
#include<iomanip>
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
	
	Catalogue leCatalogue = Catalogue();
	char * villeDepartInit = new char[20];
	char * villeArriveeInit = new char[20];
	char * moyenDeTransportInit = new char[20];
	strcpy(villeDepartInit, "Lyon");
	strcpy(villeArriveeInit, "Avignon");
	strcpy(moyenDeTransportInit, "TGV");
	char * action = new char[50];
	TrajetSimple * trajetsSimples[50];
	const TrajetSimple * trajetsSimplesComposants[50];
	TrajetCompose * trajetsComposes[50];
	unsigned cptTrajetsSimples = 0;
	unsigned cptTrajetsComposes = 0;
	unsigned cptTrajetsSimplesComposants = 0;
	string nomFichier=" ";



	char choix = '0';
	cout << endl << "Bienvenue dans Traj'App++ " << endl;
	do
	{
		cout << endl;
		cout << "====================== MENU ======================" << endl;
		cout << "Que souhaitez-vous faire a present ?" << endl;
		cout << "0 : Afficher les trajets disponibles" << endl;
		cout << "1 : Ajouter un nouveau trajet simple" << endl;
		cout << "2 : Ajouter un nouveau trajet compose" << endl;
		cout << "3 : Recherche simple de trajet" << endl;
		cout << "4 : Sauvegarde et chargement des trajets" << endl;
		cout << "5 : Quitter l'application" << endl;
		cin >> choix;
		cout << "==============================================" << endl;
		switch (choix)
		{
		case '0':
		{
			//leCatalogue.Afficher();
			afficherFichier();
			break;
		}



		case '1':
		{
			cout << "Saisissez la ville de depart" << endl;
			cin >> action;
			strcpy(villeDepartInit, action);
			cout << "Saisissez la ville d'arrivee" << endl;
			cin >> action;
			strcpy(villeArriveeInit, action);
			cout << "Saisissez le moyen de transport" << endl;
			cin >> action;
			strcpy(moyenDeTransportInit, action);
			trajetsSimples[cptTrajetsSimples] = new TrajetSimple(villeDepartInit, villeArriveeInit, moyenDeTransportInit);
			AjouterTrajet(*trajetsSimples[cptTrajetsSimples]);
			cptTrajetsSimples++;
			break;

		}



		case '2':
		{
			cout << "Les entrees ne doivent pas comporter d'espaces !" << endl;
			cout << "Un trajet compose comporte au moins 2 villes" << endl;
			cout << "Entrez STOP pour valider la saisie du trajet" << endl;
			int i = 0;
			cout << "Ville de depart : ";
			cin >> action;
			strcpy(villeDepartInit, action);
			cout << "Ville de d'arrivee : ";
			cin >> action;
			strcpy(villeArriveeInit, action);
			
			do
			{
				cout << "Moyen de Transport : ";
				cin >> action;
				strcpy(moyenDeTransportInit, action);
				trajetsSimplesComposants[cptTrajetsSimplesComposants] = new TrajetSimple(villeDepartInit, villeArriveeInit, moyenDeTransportInit);
				
				if (i == 0)
				{
					trajetsComposes[cptTrajetsComposes] = new TrajetCompose(*trajetsSimplesComposants[cptTrajetsSimplesComposants]);
				}
				else
				{

					trajetsComposes[cptTrajetsComposes]->Ajouter(*trajetsSimplesComposants[cptTrajetsSimplesComposants]);
				}
				i++;
					//cout << "coucou" << endl;
					strcpy(villeDepartInit, villeArriveeInit);
					cptTrajetsSimplesComposants++;
					cout << "Etape suivante (ou STOP) : ";
				
			

			} while (cin >> action && strcpy(villeArriveeInit, action) && strcmp(action, "STOP") != 0);
			//cptTrajetsSimplesComposants++;
			AjouterTrajet(*trajetsComposes[cptTrajetsComposes]);
			cptTrajetsComposes++;
			break;
		}



		case '3':
		{
			cout << "Saisissez la ville de depart" << endl;
			cin >> action;
			strcpy(villeDepartInit, action);
			cout << "Saisissez la ville d'arrivee" << endl;
			cin >> action;
			strcpy(villeArriveeInit, action);
			RechercherParcoursSimple(villeDepartInit, villeArriveeInit);
			break;
		}

		case '4':
		{
			
			cout << "Veuillez entrez le nom du fichier que vous voulez sauvegarder" << endl;
			cin >> nomFichier;
			Sauvegarde1(nomFichier);
			break;
		}


		case '5':
		{
			delete[] action;
			for (unsigned i(0); i < cptTrajetsSimples; i++) {
				delete trajetsSimples[i];
			}
			for (unsigned i(0); i < cptTrajetsSimplesComposants; i++) {
				delete trajetsSimplesComposants[i];
			}
			for (unsigned i(0); i < cptTrajetsComposes; i++) {
				delete trajetsComposes[i];
			}
			delete[] villeDepartInit;
			delete[] villeArriveeInit;
			delete[] moyenDeTransportInit;
			cout << "A la prochaine :-)" << endl;
			break;

		}
		default:
		{
			cout << "Saisissez un chiffre entre 0 et 5 s'il vous plait !" << endl;
		}
		}
	} while (choix != '5');
}


void Catalogue::Afficher() const
{
  const int nbTrajets = trajetsDisponibles.EnvoyerCard();
  if (nbTrajets == 0)
  {
	  cout << "Votre catalogue est vide" << endl;
  }
  else
  {
	  for (int i(0); i < nbTrajets; i++)
	  {

		  cout << i + 1 << "  : ";
		  const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
		  iemeTrajet.Afficher();
		  cout << '\n';
	  }
  }
}

void Catalogue::afficherFichier() const
{
  const int nbTrajets = trajetsDisponibles.EnvoyerCard();
  if (nbTrajets == 0)
  {
	  cout << "Votre catalogue est vide" << endl;
  }
  else
  {
	  for (int i(0); i < nbTrajets; i++)
	  {
		  const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
		  string typeTrajet;
		  if (iemeTrajet.EnvoyerType())
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
}

void Catalogue::AjouterTrajet(const Trajet & t)
{
  trajetsDisponibles.Ajouter(t);
}

void Catalogue::RechercherParcoursSimple(const char *  vDep, const char *  vFin) const
{
    //cout << "Version simple :" << endl;
    const int nbTrajets = trajetsDisponibles.EnvoyerCard();
    int j = 1;
    for (int i(0) ; i < nbTrajets; i++)
    {
      const Trajet &iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
      if (strcmp(iemeTrajet.EnvoyerVilleDepart(),vDep) == 0 && strcmp(iemeTrajet.EnvoyerVilleArrivee(),vFin) == 0)
      {
        cout << j++ << "  : ";
        iemeTrajet.AfficherFichier();
        cout << '\n';
      }
    }
}

bool Catalogue::Sauvegarde1(string chemin) const
{
	bool ok = false;
	ofstream fic;
	fic.open(chemin);
	if (fic)
	{
		ok= true;
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		afficherFichier();
		cout.rdbuf(oldCoutBuffer);
		fic.close();
	}
	
	return ok;
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
