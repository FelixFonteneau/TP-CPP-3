/*************************************************************************************
						   Catalogue  -  description
							 -------------------
	début                : 17/12/2018
	copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
	e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
#include <cstring>
#include <string>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"



//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

unsigned cptTrajetsSimples = 0;
unsigned cptTrajetsComposes = 0;
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
		cout << "====================== MENU PRINCIPAL ====================" << endl;
		cout << "Que souhaitez-vous faire a present ?" << endl;
		cout << "0 : Afficher les trajets disponibles" << endl;
		cout << "1 : Ajouter un nouveau trajet simple" << endl;
		cout << "2 : Ajouter un nouveau trajet compose" << endl;
		cout << "3 : Recherche simple de trajet" << endl;
		cout << "4 : Sauvegarde et chargement des trajets" << endl;
		cout << "5 : Quitter l'application" << endl;
		cin >> choix;
		cout << "===========================================================" << endl;
		switch (choix)
		{
			case '0':
			{
				Afficher();
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
				cptTrajetsSimples++;
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
				trajetComposeTmp = new TrajetCompose(trajetSimpleTmp);
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
				cptTrajetsComposes++;
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
				MenuSave();
				break;
			}

			case '5':
			{

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
	
}//Fin de Menu



void Catalogue::MenuSave()
{
	char nomFichier[20];
	char unChoix = '1';
	do
	{
		cout << endl;
		cout << "====================== MENU SAUVEGARDE/CHARGEMENT====================" << endl;
		cout << "Que souhaitez-vous sauvegarder ?" << endl;
		cout << "1 : Sauvegarder tout le catalogue" << endl;
		cout << "2 : Sauvegarde par type de trajets" << endl;
		cout << "3 : Sauvegarde selon le choix de la ville" << endl;
		cout << "4 : Sauvegarder une selection de trajets" << endl;
		cout << "5 : Charger tout le catalogue depuis un fichier" << endl;
		cout << "6 : Charger  le catalogue en fonction du type de trajet" << endl;
		cout << "7 : Charger le catalogue le choix de la ville" << endl;
		cout << "8 : Charger  le catalogue selon une selection de trajets" << endl;
		cout << "9 : Retour au menu principal" << endl;
		cin >> unChoix;
		cout << "====================================================================" << endl;
		switch (unChoix)
		{
			case '1':
			{
				cout << "Veuillez entrer le nom du fichier que vous voulez sauvegarder" << endl;
				cin >> nomFichier;
				ofstream fout;
				SauvegardeAll(fout, strcat(nomFichier, ".doc"));
				cout << "Fichier enregistré !" << endl;
				break;
			}

			case '2':
			{
				cout << "Veuillez entrer le nom du fichier que vous voulez sauvegarder" << endl;
				cin >> nomFichier;
				int nb;
				cout << "saisissez 0 pour ne sauvegarder que les trajets simples et 1 pour les trajets composées"<<endl;
				cin >> nb;
				while (nb != 0 && nb != 1)
				{
					cout << "Veuillez saisir 0 pour les trajets simples et 1 pour les trajets composés "<<endl;
					cin >> nb;
				}
				ofstream fout;
				SauvegardeType(fout, strcat(nomFichier, ".doc"),nb);
				cout << "Fichier enregistré !" << endl;
				break;
			}

			case '3':
			{
				MenuSaveVille();
				break;
			}

			case '4':
			{
				cout << "Veuillez entrer un nombre entre 1 et"<< cptTrajetsSimples + cptTrajetsComposes <<endl;
				unsigned int n;
				unsigned int m ;
				cout << "Entrez la borne inferieur de l'intervalle" << endl;
				cin >> n;
				while(n < 1 || n >cptTrajetsSimples+ cptTrajetsComposes)
				{
					cout << "Veuillez entrez un nombre entre 1 et " << cptTrajetsSimples + cptTrajetsComposes <<endl;
					cin >> n;
				}
				cout << "Entrez la borne supérieur de l'intervalle" << endl;
				cin >> m;
				while (m<n || m>cptTrajetsSimples + cptTrajetsComposes)
				{
					cout << "Veuillez entrez un nombre entre 1 et " << cptTrajetsSimples + cptTrajetsComposes <<endl;
					cin >> m;
				}
				cout << "Veuillez entrer le nom du fichier que vous voulez sauvegarder" << endl;
				cin >> nomFichier;
				ofstream fout;
				SauvegardeSelec(fout, strcat(nomFichier, ".doc"), n,m);
				cout << "Fichier enregistré !" << endl;
				break;
			}

			case '5':
			{
				string cheminFichier;
				cout << "Saisissez le chemin d'acces pour votre Sauvegarde. Si le fichier existe déjà il sera remplacé." << endl;
				cin >> cheminFichier;
				if (!ChargementAll(nomFichier))
				{
					cout << "erreur de chargement dans le fichier : " << cheminFichier << endl;
				}
				else
				{
					cout << "Chargé !" << endl;
				}
				break;
				
			}

			case '6':
			{
				string cheminFichier;
				cout << "Saisissez le chemin d'acces pour votre Sauvegarde. Si le fichier existe déjà il sera remplacé." << endl;
				cin >> cheminFichier;
				int nb;
				cout << "saisissez 0 pour ne sauvegarder que les trajets simples et 1 pour les trajets composées" << endl;
				cin >> nb;
				while (nb != 0 && nb != 1)
				{
					cout << "Veuillez saisir 0 pour les trajets simples et 1 pour les trajets composés " << endl;
					cin >> nb;
				}
				if (!ChargementType(nomFichier,nb))
				{
					cout << "erreur de chargement dans le fichier : " << cheminFichier << endl;
				}
				else
				{
					cout << "Chargé !" << endl;
				}
				break;
			}

			case '7':
			{
				MenuSaveVille();
				break;
			}
			case '8':
			{
				/*int nbLignes = 0;
				string cheminFichier;
				cout << "Saisissez le chemin d'acces pour votre Sauvegarde." << endl;
				cin >> cheminFichier;
				string lignes;
				ifstream in(" C:\\Users\\Houda\\Desktop\\Programmation\\TP-CPP-3-master\\Code\\test14.doc");
				while (getline(in, lignes))
				{
					nbLignes++;
				}

				cout << "Veuillez entrer un nombre entre 1 et" << nbLignes << endl;
				unsigned int n;
				unsigned int m;
				cout << "Entrez la borne inferieur de l'intervalle" << endl;
				cin >> n;
				while (n < 1 || n > nbLignes)
				{
					cout << "Veuillez entrez un nombre entre 1 et " << nbLignes << endl;
					cin >> n;
				}
				cout << "Entrez la borne supérieur de l'intervalle" << endl;
				cin >> m;
				while (m<n || m> nbLignes)
				{
					cout << "Veuillez entrez un nombre entre 1 et " << nbLignes << endl;
					cin >> m;
				}

				if (!ChargementSelection(nomFichier,n,m))
				{
					cout << "erreur de chargement dans le fichier : " << cheminFichier << endl;
				}
				else
				{
					cout << "Chargé !" << endl;
				}
				*/
				cout << "méthode non fonctionnel" << endl;
				break;
			}
			case '9':
			{
				Menu();
				break;
			}

			default:
			{
			cout << "Saisissez un chiffre entre 1 et 9 s'il vous plait !" << endl;
			}
		}
	} while (unChoix != '9');
}//Fin de MenuSave


		void Catalogue::MenuSaveVille()
		{
			char nomFichier[20];
			char leChoix = '1';
			char action[20];
			char action1[20];
			do
			{
				cout << endl;
				cout << "====================== SAUVEGARDE/CHARGEMENT VILLE====================" << endl;
				cout << "1 : Sauvegarder selon la ville de départ" << endl;
				cout << "2 : Sauvegarder selon la ville d'arrivée" << endl;
				cout << "3 : Sauvegarde selon la ville de départ et d'arrivée" << endl;
				cout << "4 : Chargement selon la ville de départ" << endl;
				cout << "5 : Chargement selon la ville d'arrivée" << endl;
				cout << "6 : Chargement selon la ville de départ et d'arrivée" << endl;
				cout << "7 : Retour au menu de sauvegarde" << endl;
				cin >> leChoix;
				cout << "============================================================" << endl;
				switch (leChoix)
				{
					case '1':
					{
						cout << "Veuillez entrer le nom de la ville de départ"<<endl;
						cin >> action;
						cout << "Veuillez entrez le nom du fichier que vous voulez sauvegarder" << endl;
						cin >> nomFichier;
						ofstream fout;
						SauvegardeVD(fout, strcat(nomFichier, ".doc"), action);
						cout << "Fichier enregistré !" << endl;
						break;
					}

					case '2':
					{
						cout << "Veuillez entrer le nom de la ville d'arrivée"<<endl;
						cin >> action;
						cout << "Veuillez entrer le nom du fichier que vous voulez sauvegarder" << endl;
						cin >> nomFichier;
						ofstream fout;
						SauvegardeVA(fout, strcat(nomFichier, ".doc"), action);
						cout << "Fichier enregistré !" << endl;
						break;
					}

					case '3':
					{
						cout << "Veuillez entrer le nom de la ville de départ"<<endl;
						cin >> action1;
						cout << "Veuillez entrer le nom de la ville d'arrivee"<<endl;
						cin >> action;
						cout << "Veuillez entrer le nom du fichier que vous voulez sauvegarder" << endl;
						cin >> nomFichier;
						ofstream fout;
						SauvegardeVDA(fout, strcat(nomFichier,".doc"), action1, action);
						cout << "Fichier enregistré !" << endl;
						break;
					}

					case '4':
					{
						/*string cheminFichier;
						cout << "Veuillez entrer le nom de la ville de départ" << endl;
						cin >> action;
						cout << "Saisissez le chemin d'acces pour votre Sauvegarde."<< endl;
						cin >> cheminFichier;

					
						if (!ChargementVD(cheminFichier,action))
						{
							cout << "erreur de chargement dans le fichier : " << nomFichier << endl;
						}
						else
						{
							cout << "Chargé !" << endl;
						}
						
						*/
						cout << "méthode non fonctionnel" << endl;

						break;
					}

					case '5':
					{
						/*cout << "Veuillez entrer le nom de la ville de d'arrivé" << endl;
						cin >> action;
						cout << "Saisissez le chemin d'acces pour votre Sauvegarde." << endl;
						cin >> nomFichier;

						if (!ChargementVA(nomFichier, action))
						{
							cout << "erreur de chargement dans le fichier : " << nomFichier << endl;
						}
						else
						{
							cout << "Chargé !" << endl;
						}
						*/
						cout << "méthode non fonctionnel" << endl;
						break;
					}

					case '6':
					{
						/*cout << "Veuillez entrer le nom de la ville de départ" << endl;
						cin >> action;
						cout << "Veuillez entrer le nom de la ville de d'arrivé" << endl;
						cin >> action1;
						cout << "Saisissez le chemin d'acces pour votre Sauvegarde." << endl;
						cin >> nomFichier;

						if (!ChargementVDA(nomFichier, action,action1))
						{
							cout << "erreur de chargement dans le fichier : " << nomFichier << endl;
						}
						else
						{
							cout << "Chargé !" << endl;
						}
						*/
						cout << "méthode non fonctionnel" << endl;
						break;
						
					}

					case '7':
					{
						MenuSave();
						break;
					
					}

					default:
					{
					cout << "Saisissez un chiffre entre 1 et 7 s'il vous plait !" << endl;
					}
				}
			} while (leChoix != '7');
		}//Fin de MenuSaveVille


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
}//Finde Afficher



void Catalogue::AjouterTrajet(const Trajet * t)
{
  trajetsDisponibles.Ajouter(t);
}

void Catalogue::RechercherParcoursSimple(const char *  vDep, const char *  vFin) const
{
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
}//Fin de AjouterTrajet

bool Catalogue::SauvegardeAll(ofstream & fout,const char chemin[20]) const
{
	bool save = false;
	int trajetsSaved = 0;
	fout.open(chemin);
	if (fout)
	{
		const int nbTrajets = trajetsDisponibles.EnvoyerCard();
		for (int i = 0; i < nbTrajets; i++)
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
			fout << typeTrajet;
			iemeTrajet.Enregistrer(fout);
			trajetsSaved++;
			fout << endl;
		}
		save = true;
	}
	else
	{
		cerr << "impossible d'ouvrir le fichier";
		
	}
	fout.close();
	if (trajetsSaved == 0)
	{
		cout << "Aucun Trajet n'a été inséré dans le fichier" << endl;
	}
	return save;
}//Fin de SauvegardeAll

bool Catalogue::SauvegardeType(ofstream & fout, const char chemin[20],bool type) const
{
	int trajetsSaved = 0;
	bool save = false;
	fout.open(chemin);
	if (fout)
	{
		const int nbTrajets = trajetsDisponibles.EnvoyerCard();
		for (int i = 0; i < nbTrajets; i++)
		{
			const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
			string typeTrajet;
			if (iemeTrajet.EnvoyerType() == type)
			{
				if (type)
				{
					typeTrajet = "TC";
				}
				else
				{
					typeTrajet = "TS";
				}
				fout << typeTrajet;
				iemeTrajet.Enregistrer(fout);
				trajetsSaved++;
				fout << endl;
				save = true;
			}

		}
	}
	else
	{
		cerr << "impossible d'ouvrir le fichier";
	}
	fout.close();
	if (trajetsSaved == 0)
	{
		cout << "Aucun Trajet n'a été inséré dans le fichier" << endl;
	}
	return save;
}//Fin de SauvegardeType

bool Catalogue::SauvegardeVD(ofstream & fout, const char chemin[20], const char vd[20]) const
{
	bool save = false;
	int trajetsSaved = 0;
	fout.open(chemin);
	if (fout)
	{
		const int nbTrajets = trajetsDisponibles.EnvoyerCard();
		for (int i = 0; i < nbTrajets; i++)
		{
			const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
			string typeTrajet;
			if (strcmp(iemeTrajet.EnvoyerVilleDepart(), vd) == 0)
			{
				if (iemeTrajet.EnvoyerType())
				{

					typeTrajet = "TC";
				}
				else
				{
					typeTrajet = "TS";
				}
				fout << typeTrajet;
				iemeTrajet.Enregistrer(fout);
				trajetsSaved++;
				fout << endl;
			}
				save = true;
		}

	}
	else
	{
		cerr << "impossible d'ouvrir le fichier";
	}
	fout.close();
	if (trajetsSaved == 0)
	{
		cout << "Aucun Trajet n'a été inséré dans le fichier" << endl;
	}
	return save;
}//Fin de SauvegardeVD


bool Catalogue::SauvegardeVA(ofstream & fout, const char chemin[20], const char va[20]) const
{
	bool save = false;
	int trajetsSaved = 0;
	fout.open(chemin);
	if (fout)
	{
		const int nbTrajets = trajetsDisponibles.EnvoyerCard();
		for (int i = 0; i < nbTrajets; i++)
		{
			const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
			string typeTrajet;
			if (strcmp(iemeTrajet.EnvoyerVilleArrivee(), va) == 0)
			{
				if (iemeTrajet.EnvoyerType())
				{

					typeTrajet = "TC";
				}
				else
				{
					typeTrajet = "TS";
				}
				fout << typeTrajet;
				iemeTrajet.Enregistrer(fout);
				trajetsSaved++;
				fout << endl;
			}
			save = true;
		}
	}
	else
	{
		cerr << "impossible d'ouvrir le fichier";
	}
	fout.close();
	if (trajetsSaved == 0)
	{
		cout << "Aucun Trajet n'a été inséré dans le fichier" << endl;
	}
	return save;
}//Fin de SauvegardeVA

bool Catalogue::SauvegardeVDA(ofstream & fout, const char chemin[20], const char vd[20], const char va[20]) const
{
	bool save = false;
	int trajetsSaved = 0;
	fout.open(chemin);
	if (fout)
	{
		const int nbTrajets = trajetsDisponibles.EnvoyerCard();
		for (int i = 0; i < nbTrajets; i++)
		{
			const Trajet& iemeTrajet = trajetsDisponibles.EnvoyerNiemeTrajet(i);
			string typeTrajet;
			if (strcmp(iemeTrajet.EnvoyerVilleDepart(), vd) == 0 && strcmp(iemeTrajet.EnvoyerVilleArrivee(), va) == 0)
			{
				if (iemeTrajet.EnvoyerType())
				{

					typeTrajet = "TC";
				}
				else
				{
					typeTrajet = "TS";
				}
				fout << typeTrajet;
				iemeTrajet.Enregistrer(fout);
				trajetsSaved++;
				fout << endl;
			}
			save = true;
		}
	}
	else
	{
		cerr << "impossible d'ouvrir le fichier";
	}
	fout.close();
	if (trajetsSaved == 0)
	{
		cout << "Aucun Trajet n'a été inséré dans le fichier" << endl;
	}
	return save;
}
//Fin de SauvegardeVDA

bool Catalogue::SauvegardeSelec(ofstream & fout, const char chemin[20], const unsigned int n,const unsigned int m) const
{
	bool save = false;
	int trajetsSaved = 0;
	fout.open(chemin);
	if (fout)
	{
		//const int nbTrajets = trajetsDisponibles.EnvoyerCard();
		for (unsigned int i = n-1; i < m; i++)
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
			fout << typeTrajet;
			iemeTrajet.Enregistrer(fout);
			trajetsSaved++;
			fout << endl;
		}
		save = true;
	}
	else
	{
		cerr << "impossible d'ouvrir le fichier";

	}
	fout.close();
	if (trajetsSaved == 0)
	{
		cout << "Aucun Trajet n'a été inséré dans le fichier" << endl;
	}
	return save;
}//Fin de SauvegardeSelec

bool Catalogue::ChargementAll(string chemin)
{
	ifstream fichierEntree(chemin);
	bool acharge;
	string nbComposants; 
	if ((acharge = !fichierEntree.fail()))
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
				fichierEntree >> nbComposants;
				//convertir le string pris du flux d'entrée en entier
				int entier = nbComposants[0]-48;
				TrajetCompose* trajetComposeRetour;
				//cout << entier;
				for( int j=0 ; j < entier ; j++)
				{
					//Allouer l'espace mémoire pour la première fois
					if (j == 0)
					{
						trajetComposeRetour = new TrajetCompose(creerTrajetSimple(fichierEntree));
					}
					else
					{
						trajetComposeRetour->Ajouter(creerTrajetSimple(fichierEntree));
					}
				}
				AjouterTrajet(trajetComposeRetour);
			}
		}
		//mettre à jour ne nb de trajets simples
		//utile pour la sauvegarde par selection 
		cptTrajetsSimples = cptTrajetsSimples + i/2;	
	}

	return acharge;	
}//Fin de Chargement

bool Catalogue::ChargementType(string chemin,bool type)
{
	ifstream fichierEntree(chemin);
	bool acharge;
	string nbComposants;
	if ((acharge = !fichierEntree.fail()))
	{
		string motTemporaire;
		int i = 0;
		while (fichierEntree >> motTemporaire)
		{
			

			if (motTemporaire.compare("TS") == 0 && type==0)
			{
				AjouterTrajet(creerTrajetSimple(fichierEntree));
				i++;
			}
			else if (motTemporaire.compare("TC") == 0 && type==1)
			{
				fichierEntree >> nbComposants;
				//convertir le string pris du flux d'entrée en entier
				int entier = nbComposants[0] - 48;
				TrajetCompose* trajetComposeRetour;
				for (int j = 0; j < entier; j++)
				{
					//Allouer l'espace mémoire pour la première fois
					if (j == 0)
					{
						trajetComposeRetour = new TrajetCompose(creerTrajetSimple(fichierEntree));
					}
					else
					{
						trajetComposeRetour->Ajouter(creerTrajetSimple(fichierEntree));
					}
				}
				AjouterTrajet(trajetComposeRetour);
				i++;
			}
		}
		//mettre à jour ne nb de trajets simples
		//utile pour la sauvegarde par selection 
		cptTrajetsSimples = cptTrajetsSimples + i ;
	}

	return acharge;
}//Fin de Chargement

/*bool Catalogue::ChargementVD(string chemin,const char vd[20])
{
	ifstream fichierEntree(chemin);
	bool acharge;
	string nbComposants;
	if ((acharge = !fichierEntree.fail()))
	{
		string motTemporaire;
		int i = 0;
		TrajetSimple* test;
		while (fichierEntree >> motTemporaire)
		{
			if (motTemporaire.compare("TS") == 0)
			{ 

				test = creerTrajetSimple(fichierEntree);
				if (strcmp(test->EnvoyerVilleDepart(), vd) == 0)
				{
					AjouterTrajet(test);
					i++;
				}
			}
			else if (motTemporaire.compare("TC") == 0 )
			{
				fichierEntree >> nbComposants;
				//convertir le string pris du flux d'entrée en entier
				int entier = nbComposants[0] - 48;
				TrajetCompose* trajetComposeRetour;
				for (int j = 0; j < entier; j++)
				{
					//Allouer l'espace mémoire pour la première fois
					if (j == 0)
					{
						trajetComposeRetour = new TrajetCompose(creerTrajetSimple(fichierEntree));
					}
					else
					{
						trajetComposeRetour->Ajouter(creerTrajetSimple(fichierEntree));
					}
				}
				if (strcmp(trajetComposeRetour->EnvoyerVilleDepart(), vd) == 0)
				{
					AjouterTrajet(trajetComposeRetour);
					i++;
				}
			}
		}
		//mettre à jour ne nb de trajets simples
		//utile pour la sauvegarde par selection 
		cptTrajetsSimples = cptTrajetsSimples + i ;
	}

	return acharge;
}//Fin de Chargement
bool Catalogue::ChargementVA(string chemin,const char va[20])
{
	ifstream fichierEntree(chemin);
	bool acharge;
	string nbComposants;
	if ((acharge = !fichierEntree.fail()))
	{
		string motTemporaire;
		int i = 0;
		while (fichierEntree >> motTemporaire)
		{


			if (motTemporaire.compare("TS") == 0 )
			{
				if (strcmp(creerTrajetSimple(fichierEntree)->EnvoyerVilleArrivee(), va) == 0)
				{
					AjouterTrajet(creerTrajetSimple(fichierEntree));
					i++;
				}
			}
			else if (motTemporaire.compare("TC") == 0 )
			{
				fichierEntree >> nbComposants;
				//convertir le string pris du flux d'entrée en entier
				int entier = nbComposants[0] - 48;
				TrajetCompose* trajetComposeRetour;
				for (int j = 0; j < entier; j++)
				{
					//Allouer l'espace mémoire pour la première fois
					if (j == 0)
					{
						trajetComposeRetour = new TrajetCompose(creerTrajetSimple(fichierEntree));
					}
					else
					{
						trajetComposeRetour->Ajouter(creerTrajetSimple(fichierEntree));
					}
				}
				if (strcmp(trajetComposeRetour->EnvoyerVilleArrivee(), va) == 0)
				{
					AjouterTrajet(trajetComposeRetour);
					i++;
				}
			}
		}
		//mettre à jour ne nb de trajets simples
		//utile pour la sauvegarde par selection 
		cptTrajetsSimples = cptTrajetsSimples + i;
	}

	return acharge;
}//Fin de Chargement
bool Catalogue::ChargementVDA(string chemin,const char vd[20],const char va[20])
{
	ifstream fichierEntree(chemin);
	bool acharge;
	string nbComposants;
	if ((acharge = !fichierEntree.fail()))
	{
		string motTemporaire;
		int i = 0;
		while (fichierEntree >> motTemporaire)
		{


			if (motTemporaire.compare("TS") == 0 )
			{
				if (strcmp(creerTrajetSimple(fichierEntree)->EnvoyerVilleDepart(), vd) == 0 && strcmp(creerTrajetSimple(fichierEntree)->EnvoyerVilleArrivee(), va) == 0)
				{
					AjouterTrajet(creerTrajetSimple(fichierEntree));
					i++;
				}
			}
			else if (motTemporaire.compare("TC") == 0 )
			{
				fichierEntree >> nbComposants;
				//convertir le string pris du flux d'entrée en entier
				int entier = nbComposants[0] - 48;
				TrajetCompose* trajetComposeRetour;
				for (int j = 0; j < entier; j++)
				{
					//Allouer l'espace mémoire pour la première fois
					if (j == 0)
					{
						trajetComposeRetour = new TrajetCompose(creerTrajetSimple(fichierEntree));
					}
					else
					{
						trajetComposeRetour->Ajouter(creerTrajetSimple(fichierEntree));
					}
				}
				if (strcmp(creerTrajetSimple(fichierEntree)->EnvoyerVilleDepart(), vd) == 0 && strcmp(creerTrajetSimple(fichierEntree)->EnvoyerVilleArrivee(), va) == 0)
				{
					AjouterTrajet(trajetComposeRetour);
					i++;
				}
			}
		}
		//mettre à jour ne nb de trajets simples
		//utile pour la sauvegarde par selection 
		cptTrajetsSimples = cptTrajetsSimples + i;
	}

	return acharge;
}//Fin de Chargement
bool Catalogue::ChargementSelection(string chemin,const int n, const int m)
{
	ifstream fichierEntree(chemin);
	bool acharge;
	string nbComposants;
	if ((acharge = !fichierEntree.fail()))
	{
		string motTemporaire;
		int i = 0;
		while (fichierEntree >> motTemporaire)
		{


			if (motTemporaire.compare("TS") == 0 )
			{
				i++;
				if (i >= n && i >= m) 
				{
					AjouterTrajet(creerTrajetSimple(fichierEntree));
				}
			}
			else if (motTemporaire.compare("TC") == 0 )
			{
				i++;
				fichierEntree >> nbComposants;
				//convertir le string pris du flux d'entrée en entier
				int entier = nbComposants[0] - 48;
				TrajetCompose* trajetComposeRetour;
				for (int j = 0; j < entier; j++)
				{
					//Allouer l'espace mémoire pour la première fois
					if (j == 0)
					{
						trajetComposeRetour = new TrajetCompose(creerTrajetSimple(fichierEntree));
					}
					else
					{
						trajetComposeRetour->Ajouter(creerTrajetSimple(fichierEntree));
					}
				}
				if (i >= n && i >= m)
				{
					AjouterTrajet(trajetComposeRetour);
				}
				
			}
		}
		//mettre à jour ne nb de trajets simples
		//utile pour la sauvegarde par selection 
		cptTrajetsSimples = cptTrajetsSimples + i;
	}

	return acharge;
}//Fin de Chargement
*/

TrajetSimple* Catalogue::creerTrajetSimple(ifstream &fichierEntree)
{
	char * villeDtmp = new char[20];
	char * villeAtmp = new char[20];
	char * moyenDeTtmp = new char[20];
	fichierEntree >> villeDtmp;
	fichierEntree >> villeAtmp;
	fichierEntree >> moyenDeTtmp;
	TrajetSimple* trajetSimpleRetour = new TrajetSimple(villeDtmp, villeAtmp, moyenDeTtmp);
	delete[] villeDtmp;
	delete[] villeAtmp;
	delete[] moyenDeTtmp;
	return trajetSimpleRetour;
}//Fin de creerTrajetSimple





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

