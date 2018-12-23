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
#include <iostream>
#include <fstream>
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
	TrajetSimple * trajetSimpleTmp;
	TrajetCompose * trajetComposeTmp;
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
		cout << "4 : Sauvegarder le catalogue actuel" <<endl;
		cout << "5 : Charger un catalogue depuis un fichier" << endl;
		cout << "6 : Quitter l'application" << endl;
		cin >> choix;
		cout << "==============================================" << endl;
		switch (choix)
		{
		case '0':
		{
			Afficher();
			//afficherFichier();
			break;
		}
		case '1':
		{
			cout << "Saisissez la ville de depart" << endl;
			cin >> villeDepartInit;
			cout << "Saisissez la ville d'arrivee" << endl;
			cin >> villeArriveeInit;
			cout << "Saisissez le moyen de transport" << endl;
			cin >> moyenDeTransportInit;
			trajetSimpleTmp = new TrajetSimple(villeDepartInit, villeArriveeInit, moyenDeTransportInit);
			AjouterTrajet(trajetSimpleTmp);
			break;
		}
		case '2':
		{
			cout << "Les entrees ne doivent pas comporter d'espaces !" << endl;
			cout << "Un trajet compose comporte au moins 2 villes" << endl;
			cout << "Entrez STOP pour valider la saisie du trajet" << endl;
			cout << "Ville de depart : ";
			cin >> villeDepartInit;
			cout << "Ville de d'arrivee : ";
			cin >> villeArriveeInit;
			cout << "Moyen de Transport : ";
			cin >> moyenDeTransportInit;
			trajetSimpleTmp = new TrajetSimple(villeDepartInit, villeArriveeInit, moyenDeTransportInit);
			trajetComposeTmp =  new TrajetCompose(trajetSimpleTmp);
			strcpy(villeDepartInit, villeArriveeInit);
			cout << "Etape suivante : ";
			cin >> villeArriveeInit;
			do
			{
				cout << "Moyen de Transport : ";
				cin >> moyenDeTransportInit;
				trajetSimpleTmp = new TrajetSimple(villeDepartInit, villeArriveeInit, moyenDeTransportInit);
				trajetComposeTmp->Ajouter(trajetSimpleTmp);
				strcpy(villeDepartInit, villeArriveeInit);
				cout << "Etape suivante (ou STOP) : ";
			} while (cin >> villeArriveeInit && strcmp(villeArriveeInit, "STOP") != 0);
			AjouterTrajet(trajetComposeTmp);
			break;
		}
		case '3':
		{
			cout << "Saisissez la ville de depart" << endl;
			cin >> villeDepartInit;
			cout << "Saisissez la ville d'arrivee" << endl;
			cin >> villeArriveeInit;
			RechercherParcoursSimple(villeDepartInit, villeArriveeInit);
			break;
		}
		case '4':
		{
			string cheminFichier;
			cout << "Saisissez le chemin d'acces pour votre Sauvegarde. Si le fichier existe déjà il sera remplacé." << endl;
			cin >> cheminFichier;
			if ( !SauvegardeComplete(cheminFichier))
			{
				cout << "erreur de sauvegarde dans le fichier : " << cheminFichier << endl;
			}
			else
			{
				cout << "Sauvegardé !" <<endl;
			}
			break;
		}
		case '5':
		{
			string cheminFichier;
			cout << "Saisissez le chemin d'acces pour votre Sauvegarde. Si le fichier existe déjà il sera remplacé." << endl;
			cin >> cheminFichier;
			if ( !Chargement(cheminFichier))
			{
				cout << "erreur de chargement dans le fichier : " << cheminFichier << endl;
			}
			else
			{
				cout << "Chargé !" <<endl;
			}
			break;
		}

		case '6':
		{
			delete[] villeDepartInit;
			delete[] villeArriveeInit;
			delete[] moyenDeTransportInit;
			cout << "A la prochaine :-)" << endl;
			break;
		}
		default:
		{
			cout << "Saisissez un chiffre entre 0 et 6 s'il vous plait !" << endl;
		}
	}
	} while (choix != '6');
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
    cout << typeTrajet << " ";
    iemeTrajet.AfficherFichier();
    cout << " ;\n";
  }
}

void Catalogue::AjouterTrajet(const Trajet * t)
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

bool Catalogue::SauvegardeComplete(string chemin) const
{
	bool ok = false;
	ofstream fic;
	fic.open(chemin);
	if (fic)
	{
		ok = true;
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		afficherFichier();
		cout.rdbuf(oldCoutBuffer);
		fic.close();
	}
	return ok;
}

bool Catalogue::Chargement(string chemin)
{
	ifstream fichierEntree(chemin);
	bool acharge;
	if((acharge = !fichierEntree.fail()))
	{
		string motTemporaire;
		int i = 0;
		while (fichierEntree >> motTemporaire)
		{
			cout << ++i << endl;
			if (motTemporaire.compare("TS") == 0)
			{
				AjouterTrajet(creerTrajetSimple(fichierEntree));
			}
			else if (motTemporaire.compare("TC") == 0)
			{
				cout << "trajet compose";
			}
		}
	}
	return acharge;
}

TrajetSimple* Catalogue::creerTrajetSimple(ifstream &fichierEntree)
{
	char * villeDtmp = new char[20];
	char * villeAtmp = new char[20];
	char * moyenDeTtmp = new char[20];
	fichierEntree >> villeDtmp;
	fichierEntree >> villeAtmp;
	fichierEntree >> moyenDeTtmp;
	TrajetSimple* trajetSimpleRetour = new TrajetSimple(villeDtmp,villeAtmp,moyenDeTtmp);
	delete [] villeDtmp;
	delete [] villeAtmp;
	delete [] moyenDeTtmp;
	return trajetSimpleRetour;

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
