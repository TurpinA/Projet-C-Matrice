#include "CSommet.h"

#define ArrivantDejaPresent 10
#define PartantDejaPresent 11
#define ArcNonPresent 14

/***
**** Nom:			CSommet
****
**** Description:	Constructeur de confort prenant en parametre le numero du sommet
****
**** Precondition:
**** Entree:		unsigned int uiNumero
**** Entraine:		Creation d'un objet CSommet
**** Sortie:
***/
CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	uiSOMNbArrivant = 0;
	uiSOMNbPartant = 0;

	pARCSOMArrivant = (CArc**)malloc(DEFAULT_SIZE_SOMMET * sizeof(CArc*));
	pARCSOMPartant = (CArc**)malloc(DEFAULT_SIZE_SOMMET * sizeof(CArc*));
}

/***
**** Nom:			CSommet
****
**** Description:	Constructeur de recopie
****
**** Precondition:
**** Entree:		CSommet & SOMSommet
**** Entraine:		Creation d'un objet CSommet
**** Sortie:
***/
CSommet::CSommet(CSommet & SOMSommet)
{
	unsigned int uiBoucle = 0;

	uiSOMNbArrivant = SOMSommet.SOMLireNbArrivant();
	uiSOMNbPartant = SOMSommet.SOMLireNbPartant();
	uiSOMNumero = SOMSommet.SOMLireNumero();

	pARCSOMArrivant = (CArc**)malloc(sizeof(CArc*) * uiSOMNbArrivant);
	pARCSOMPartant = (CArc**)malloc(sizeof(CArc*) * uiSOMNbPartant);

	for (uiBoucle = 0; uiBoucle < uiSOMNbArrivant; uiBoucle++)
	{
		pARCSOMArrivant[uiBoucle] = new CArc(*SOMSommet.pARCSOMArrivant[uiBoucle]);
	}

	for (uiBoucle = 0; uiBoucle < uiSOMNbPartant; uiBoucle++)
	{
		pARCSOMPartant[uiBoucle] = new CArc(*SOMSommet.pARCSOMPartant[uiBoucle]);
	}
}

/***
**** Nom:			~CSommet
****
**** Description:	Destructeur
****
**** Precondition:
**** Entree:		CSommet &
**** Entraine:		Desallocation et destruction de l'objet CSommet
**** Sortie:
***/
CSommet::~CSommet()
{
	unsigned int uiBoucle = 0;

	for (uiBoucle = 0; uiBoucle < uiSOMNbArrivant; uiBoucle++)
	{
		delete pARCSOMArrivant[uiBoucle];
	}
	free(pARCSOMArrivant);

	for (uiBoucle = 0; uiBoucle < uiSOMNbPartant; uiBoucle++)
	{
		delete pARCSOMPartant[uiBoucle];
	}
	free(pARCSOMPartant);
}

/***
**** Nom:			SOMAjouterArrivant
****
**** Description:	Cette methode ajoute un objet CArc dans le tableau des arrivants
****
**** Precondition:
**** Entree:		CArc & ARCArrivant
**** Entraine:		Ajout de l'arc dans le tableau des arrivants du sommet
**** Sortie:
***/
void CSommet::SOMAjouterArrivant(unsigned int uiNumero)
{
	if (!SOMArcArrivantPresent(uiNumero))
	{
		pARCSOMArrivant = (CArc**)realloc(pARCSOMArrivant, (uiSOMNbArrivant + 1) * sizeof(CArc*));
		pARCSOMArrivant[uiSOMNbArrivant] = new CArc(uiNumero);
		uiSOMNbArrivant++;
	}
	else
		throw CException(ArrivantDejaPresent, "Arrivant déjà présent");
}

/***
**** Nom:			SOMAjouterPartant
****
**** Description:	Cette methode ajoute un objet CArc dans le tableau des partants
****
**** Precondition:
**** Entree:		CArc & ARCArrivant
**** Entraine:		Ajout de l'arc dans le tableau des partants du sommet
**** Sortie:
***/
void CSommet::SOMAjouterPartant(unsigned int uiNumero)
{
	if (!SOMArcPartantPresent(uiNumero))
	{
		pARCSOMPartant = (CArc**)realloc(pARCSOMPartant, (uiSOMNbPartant + 1) * sizeof(CArc*));
		pARCSOMPartant[uiSOMNbPartant] = new CArc(uiNumero);
		uiSOMNbPartant++;
	}
	else
		throw CException(PartantDejaPresent, "Partant déjà présent");
}

/***
**** Nom:			SOMSupprimerArrivant
****
**** Description:	Cette methode supprime l'arc ayant uiNumero comme numero dans la liste des arrivant
****
**** Precondition:
**** Entree:		unsigned int uiNumero
**** Entraine:		Suppression de l'arc dans la liste des arrivants
**** Sortie:
***/
void CSommet::SOMSupprimerArrivant(unsigned int uiNumero)
{
	unsigned int uiBoucle = 0;

	if (SOMArcArrivantPresent(uiNumero))
	{
		unsigned int positionArrivant = 0;
		while (pARCSOMArrivant[positionArrivant]->ARCLireDestination() != uiNumero)
		{
			positionArrivant++;
		}

		delete pARCSOMArrivant[positionArrivant];

		for (uiBoucle = 0; uiBoucle < uiSOMNbArrivant - 1 - positionArrivant; uiBoucle++)
		{
			pARCSOMArrivant[positionArrivant] = pARCSOMArrivant[positionArrivant + 1];
			pARCSOMArrivant[positionArrivant + 1] = nullptr;
		}

		uiSOMNbArrivant--;
	}
}

/***
**** Nom:			SOMSupprimerPartant
****
**** Description:	Cette methode supprime l'arc ayant uiNumero comme numero dans la liste des partant
****
**** Precondition:
**** Entree:		unsigned int uiNumero
**** Entraine:		Suppression de l'arc dans la liste des partants
**** Sortie:
***/
void CSommet::SOMSupprimerPartant(unsigned int uiNumero)
{
	unsigned int uiBoucle = 0;

	if (SOMArcPartantPresent(uiNumero))
	{
		unsigned int positionPartant = 0;
		while (pARCSOMPartant[positionPartant]->ARCLireDestination() != uiNumero)
		{
			positionPartant++;
		}

		delete pARCSOMPartant[positionPartant];

		for (uiBoucle = 0; uiBoucle < uiSOMNbPartant - 1 - positionPartant; uiBoucle++)
		{
			pARCSOMPartant[positionPartant] = pARCSOMPartant[positionPartant + 1];
			pARCSOMPartant[positionPartant + 1] = nullptr;
		}

		uiSOMNbPartant--;
	}
}

/***
**** Nom:			SOMModifierNumero
****
**** Description:	Cette methode modifie l'attribut uiSOMNumero de l'objet
****
**** Precondition:
**** Entree:		unsigned int uiNumero
**** Entraine:		La modification de l'attribut uiSOMNumero
**** Sortie:
***/
void CSommet::SOMModifierNumero(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
}

/***
**** Nom:			SOMModifierArrivant
****
**** Description:	Cette methode modifie la destination d'un arc de la liste des arrivants
****
**** Precondition:
**** Entree:		unsigned int uiOldNumero, unsigned int uiNewNumero
**** Entraine:		Modifie la destination du numero de destination de l'arc de la liste des arrivants
**** Sortie:
***/
void CSommet::SOMModifierArrivant(unsigned int uiOldNumero, unsigned int uiNewNumero)
{
	if (SOMArcArrivantPresent(uiOldNumero))
	{
		unsigned int positionArrivant = 0;
		while (pARCSOMArrivant[positionArrivant]->ARCLireDestination() != uiOldNumero)
		{
			positionArrivant++;
		}

		pARCSOMArrivant[positionArrivant]->ARCModifierDestination(uiNewNumero);
	}
	else
		throw CException(ArcNonPresent,"Aucun arc avec ce numero n'est present dans la liste");
}

/***
**** Nom:			SOMModifierPartant
****
**** Description:	Cette methode modifie la destination d'un arc de la liste des partant
****
**** Precondition:
**** Entree:		unsigned int uiOldNumero, unsigned int uiNewNumero
**** Entraine:		Modifie la destination du numero de destination de l'arc de la liste des partant
**** Sortie:
***/
void CSommet::SOMModifierPartant(unsigned int uiOldNumero, unsigned int uiNewNumero)
{
	if (SOMArcPartantPresent(uiOldNumero))
	{
		unsigned int positionPartant = 0;
		while (pARCSOMPartant[positionPartant]->ARCLireDestination() != uiOldNumero)
		{
			positionPartant++;
		}

		pARCSOMPartant[positionPartant]->ARCModifierDestination(uiNewNumero);
	}
	else
		throw CException(ArcNonPresent, "Aucun arc avec ce numero n'est present dans la liste");
}

/***
**** Nom:			SOMArcPartantPresent
****
**** Description:	Cette methode cherche si l'arc ayant uiNumero comme destination est present dans la liste des partant
****
**** Precondition:
**** Entree:		unsigned int uiNumero
**** Entraine:		Renvoit vrai si l'arc avec uiNumero est partant, renvoit faux sinon
**** Sortie:		bool
***/
bool CSommet::SOMArcPartantPresent(unsigned int uiNumero)
{
	unsigned int uiBoucle = 0;

	bool bArcDejaPresent = false;

	for (uiBoucle = 0; uiBoucle < uiSOMNbPartant; uiBoucle++)
	{
		if (pARCSOMPartant[uiBoucle]->ARCLireDestination() == uiNumero)
			bArcDejaPresent = true;
	}
	return bArcDejaPresent;
}

/***
**** Nom:			SOMArcArrivantPresent
****
**** Description:	Cette methode cherche si l'arc ayant uiNumero comme destination est present dans la liste des arrivants
****
**** Precondition:
**** Entree:		unsigned int uiNumero
**** Entraine:		Renvoit vrai si l'arc avec uiNumero est arrivant, renvoit faux sinon
**** Sortie:		bool
***/
bool CSommet::SOMArcArrivantPresent(unsigned int uiNumero)
{
	unsigned int uiBoucle = 0;
	bool bArcPresent = false;

	for (uiBoucle = 0; uiBoucle < uiSOMNbArrivant; uiBoucle++)
	{
		if (pARCSOMArrivant[uiBoucle]->ARCLireDestination() == uiNumero)
			bArcPresent = true;
	}
	return bArcPresent;
}

/***
**** Nom:			SOMLireNumero
****
**** Description:	Cette methode renvoit l'attribut uiSOMNumero
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de l'attribut uiSOMNumero
**** Sortie:		unsigned int
***/
unsigned int CSommet::SOMLireNumero()
{
	return uiSOMNumero;
}

/***
**** Nom:			SOMLireNbArrivant
****
**** Description:	Cette methode renvoit l'attribut uiSOMNbArrivant
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de l'attribut uiSOMNbArrivant
**** Sortie:		unsigned int
***/
unsigned int CSommet::SOMLireNbArrivant()
{
	return uiSOMNbArrivant;
}

/***
**** Nom:			SOMLireNbPartant
****
**** Description:	Cette methode renvoit l'attribut uiSOMNbPartant
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de l'attribut uiSOMNbPartant
**** Sortie:		unsigned int
***/
unsigned int CSommet::SOMLireNbPartant()
{
	return uiSOMNbPartant;
}

void CSommet::SOMModifierNbArrivant(unsigned int uiNbArrivant)
{
	uiSOMNbArrivant = uiNbArrivant;
}

void CSommet::SOMModifierNbPartant(unsigned int uiNbPartant)
{
	uiSOMNbPartant = uiNbPartant;
}

CArc ** CSommet::SOMLireListeArrivant()
{
	return pARCSOMArrivant;
}

CArc ** CSommet::SOMLireListePartant()
{
	return pARCSOMPartant;
}

void CSommet::SOMModifierListeArrivant(CArc ** pARCParam)
{
	pARCSOMArrivant = pARCParam;
}

void CSommet::SOMModifierListePartant(CArc ** pARCParam)
{
	pARCSOMPartant = pARCParam;
}

/***
**** Nom:			SOMLireArrivant
****
**** Description:	Cette methode renvoit l'arc à la position uiPosition dans la liste des arrivants
****
**** Precondition:
**** Entree:		unsigned int uiPosition
**** Entraine:		Renvoit le CArc à la position uiPosition de la liste des arrivants
**** Sortie:		CArc *
***/
CArc * CSommet::SOMLireArrivant(unsigned int uiPosition)
{
	return pARCSOMArrivant[uiPosition];
}

/***
**** Nom:			SOMLirePartant
****
**** Description:	Cette methode renvoit l'arc à la position uiPosition dans la liste des partants
****
**** Precondition:
**** Entree:		unsigned int uiPosition
**** Entraine:		Renvoit le CArc à la position uiPosition de la liste des partants
**** Sortie:		CArc *
***/
CArc * CSommet::SOMLirePartant(unsigned int uiPosition)
{
	return pARCSOMPartant[uiPosition];
}

CSommet & CSommet::operator=(CSommet & SOMSommet)
{
	unsigned int uiBoucle = 0;

	if (pARCSOMArrivant != nullptr)
	{
		for (uiBoucle = 0; uiBoucle < uiSOMNbArrivant; uiBoucle++)
		{
			delete pARCSOMArrivant[uiBoucle];
		}
		free(pARCSOMArrivant);
	}

	if (pARCSOMPartant != nullptr)
	{
		for (uiBoucle = 0; uiBoucle < uiSOMNbPartant; uiBoucle++)
		{
			delete pARCSOMPartant[uiBoucle];
		}
		free(pARCSOMPartant);
	}

	uiSOMNbArrivant = SOMSommet.uiSOMNbArrivant;
	uiSOMNbPartant = SOMSommet.uiSOMNbPartant;
	uiSOMNumero = SOMSommet.uiSOMNumero;

	pARCSOMArrivant = (CArc**)malloc(sizeof(CArc*) * uiSOMNbArrivant);
	pARCSOMPartant = (CArc**)malloc(sizeof(CArc*) * uiSOMNbPartant);

	for (uiBoucle = 0; uiBoucle < uiSOMNbArrivant; uiBoucle++)
	{
		pARCSOMArrivant[uiBoucle] = new CArc(*SOMSommet.pARCSOMArrivant[uiBoucle]);
	}

	for (uiBoucle = 0; uiBoucle < uiSOMNbPartant; uiBoucle++)
	{
		pARCSOMPartant[uiBoucle] = new CArc(*SOMSommet.pARCSOMPartant[uiBoucle]);
	}

	return *this;
}



