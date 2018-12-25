/*************************************************************************************
						  TrajetSimple  -  description
							 -------------------
	début                : 17/12/2018
	copyright            : (C) 2018 par Felix FONTENEAU et Houda OUHSSAIN
	e-mail               : felix.fonteneau@insa-lyon.fr / houda.ouhssain@insa-lyon.fr
***************************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include <fstream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum eMoyenDeTransport {Train, Auto, Bateau, Avion, Velo};
//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//	Définir	un trajet par sa ville de départ, sa ville d'arrivée et son moyen de transport
//	Cette classe constitue aussi la brique de base des trajets composés, qui, peuvent être 
//  de plusieurs trajets simples ou bien d'autres trajets composés.  
//
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
  virtual bool EnvoyerType () const
  {
      return 0;
  }
    //mode d'emploi : Envoi un bool pour savoir le type du fichier
    //envoi 0 pour un trajet simple et 1 pour trajet compose.
    //en locurence envera 0 ici

  virtual void Afficher () const;

  virtual char * EnvoyerVilleDepart() const;

  virtual char * EnvoyerVilleArrivee() const;

  char * EnvoyerMoyenDeTransport() const;

  virtual void Enregistrer(ofstream & fout) const;
  // Mode d'emploi : Renvoie dans le fichier dont le flux de sortie est passé en paramètre
	//le trajet simple avec un affichage spécial fichier

//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( char * vDepart, char * vArrivee, char * mTransport );
    // Mode d'emploi: Constructeur classique
    // Contrat :
    // moyenDeTransport doit être un des élements suivants : {Train, Auto, Bateau, Avion, Velo}
    // Référence à l'ancienne version utilisant alors une énum pour réprésenter les moyens de transport

    virtual ~TrajetSimple ( );
    // Mode d'emploi : Destructeur classique

protected:

//----------------------------------------------------- Attributs protégés
	char * moyenDeTransport;
};


#endif // TRAJETSIMPLE_H
