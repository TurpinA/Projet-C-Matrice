#include "CGraphe.h"
#include <string.h>

//Exception List
#define NumeroPris 9
#define SommetIntrouvable 22
#define InvalidArgument 12
#define FormatIncorrect 11
#define GrapheVide 13


/***
**** Nom:			compareDeuxChaine
****
**** Description:	Fonction qui compare deux chaines de caractères
****
**** Precondition:
**** Entree:		char* pcChaine1, const char* pcChaine2
**** Entraine:		Renvoit un vrai si les chaines de caracteres sont égales
**** Sortie:        bool
***/
bool compareDeuxChaine(char* pcChaine1, const char* pcChaine2)
{
	bool bChaineEgal = true;

	int iParcoureur = 0, iVerifTailleChaine1 = 0, iVerifTailleChaine2 = 0;


	//On passe les espaces en trop devant la chaine de caractere
	while (*pcChaine1 == ' ' || *pcChaine1 == '\n')
	{
		pcChaine1++;
	}

	//On verifie si les chaines de caractere ont la meme taille
	while (pcChaine1[iParcoureur] != '\0')
	{
		iParcoureur++;
		iVerifTailleChaine1++;
	}

	iParcoureur = 0;

	while (pcChaine2[iParcoureur] != '\0')
	{
		iParcoureur++;
		iVerifTailleChaine2++;
	}

	iParcoureur = 0;

	if (iVerifTailleChaine1 != iVerifTailleChaine2)
		bChaineEgal = false;

	//On verifie si les chaines de caractere sont equivalentes
	while (pcChaine2[iParcoureur] != '\0' && bChaineEgal == true)
	{
		if (pcChaine1[iParcoureur] != pcChaine2[iParcoureur])
			bChaineEgal = false;
		++iParcoureur;
	}

	return bChaineEgal;
}

/***
**** Nom:			CGraphe
****
**** Description:	Constructeur par défaut
****
**** Precondition:
**** Entree:
**** Entraine:		Construction de l'objet, allocation du tableau avec une place et initialisation des attributs
**** Sortie:
***/
CGraphe::CGraphe()
{
	uiGRANbSommet = 0;
	uiGRANbArc = 0;
	uiGRATailleAlloueListe = 1;

	pSOMGRAListeSommet = (CSommet**)malloc(sizeof(CSommet*) * 1);
}

/***
**** Nom:			CGraphe
****
**** Description:	Constructeur de recopie
****
**** Precondition:
**** Entree:		CGraphe& GRAGraphe
**** Entraine:		La création d'un objet CGraphre en recopiant l'objet passee en parametre
**** Sortie:
***/
CGraphe::CGraphe(CGraphe& GRAGraphe)
{
	unsigned int uiBoucle = 0;

	uiGRANbSommet = GRAGraphe.GRALireNbSommet();
	uiGRANbArc = GRAGraphe.GRALireNbArc();
	uiGRATailleAlloueListe = GRAGraphe.GRALireTailleAlloueListe();

	pSOMGRAListeSommet = (CSommet**)malloc(sizeof(CSommet*) * uiGRATailleAlloueListe);

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		pSOMGRAListeSommet[uiBoucle] = new CSommet(*GRAGraphe.GRALireListeSommet(uiBoucle));
	}
}

/***
**** Nom:			CGraphe
****
**** Description:	Constructeur de recopie
****
**** Precondition:
**** Entree:		CGraphe& GRAGraphe
**** Entraine:		La création d'un objet CGraphre en recopiant l'objet passee en parametre
**** Sortie:
***/
CGraphe::CGraphe(CGraphe&& GRAGraphe)
{
	unsigned int uiBoucle = 0;

	uiGRANbSommet = GRAGraphe.GRALireNbSommet();
	uiGRANbArc = GRAGraphe.GRALireNbArc();
	uiGRATailleAlloueListe = GRAGraphe.GRALireTailleAlloueListe();

	pSOMGRAListeSommet = (CSommet**)malloc(sizeof(CSommet*) * uiGRATailleAlloueListe);

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		pSOMGRAListeSommet[uiBoucle] = new CSommet(*GRAGraphe.GRALireListeSommet(uiBoucle));
	}
}

/***
**** Nom:			CGraphe
****
**** Description:	Constructeur de confort
****
**** Precondition:
**** Entree:		const char* pcChemin
**** Entraine:		Creation du graphe ecrit dans le fichier texte grace a la classe CParser
****				Construction de l'objet
**** Sortie:
***/
CGraphe::CGraphe(const char* pcChemin)
{
	unsigned int uiBoucle = 0;

	CParser parser(pcChemin);
	unsigned int uiNbSommets = 0;
	unsigned int uiNbArcs = 0;

	char *cLigne;

	unsigned int uiNbSommetsVerif = 0;
	unsigned int uiNbArcsVerif = 0;

	unsigned int uiSommetDepart;
	unsigned int uiSommetArrivee;

	cLigne = parser.PARGetAttribut();

	if (!compareDeuxChaine(cLigne, "NBSommets"))
		throw CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	cLigne = parser.PARGetValeurLine();
	uiNbSommets = atoi(cLigne);

	cLigne = parser.PARGetAttribut();

	if (!compareDeuxChaine(cLigne, "NBArcs"))
		throw CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	cLigne = parser.PARGetValeurLine();
	uiNbArcs = atoi(cLigne);

	cLigne = parser.PARGetValeurLine();
	if (!compareDeuxChaine(cLigne, "Sommets=["))
		throw  CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	//SAVE CURSOR IN FILE
	parser.PARSaveCursorInFile();

	//COMPTAGE DE SOMMETS
	cLigne = parser.PARGetValeurLine();
	while (!compareDeuxChaine(cLigne, "]"))
	{
		if (!compareDeuxChaine(cLigne, ""))
			uiNbSommetsVerif++;

		cLigne = parser.PARGetValeurLine();
	}

	cLigne = parser.PARGetValeurLine();
	if (!compareDeuxChaine(cLigne, "Arcs=["))
		throw  CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	//COMPTAGE ARCS
	cLigne = parser.PARGetValeurLine();
	while (!compareDeuxChaine(cLigne, "]"))
	{
		if (!compareDeuxChaine(cLigne, ""))
			uiNbArcsVerif++;

		cLigne = parser.PARGetValeurLine();
	}

	//VERIF ARGUMENTS DONNEES
	if (uiNbSommets != uiNbSommetsVerif || uiNbArcs != uiNbArcsVerif)
		throw  CException(InvalidArgument, "INCOHERENCES ARGUMENTS");

	//On remet le curseur apres le Sommets=[
	parser.PARPlaceCursorToSave();


	//CREATION DU GRAPHE
	CGraphe grapheTempo;

	unsigned int uiVar;

	bool test = true;

	parser.PARSaveCursorInFile();
	cLigne = parser.PARGetValeurLine();
	if (!compareDeuxChaine(cLigne, "]"))
	{
		parser.PARPlaceCursorToSave();

		while (test)
		{
			parser.PARSaveCursorInFile();
			cLigne = parser.PARGetValeur();

			if (compareDeuxChaine(cLigne, "]"))
			{
				test = false;
			}
			else
			{
				parser.PARPlaceCursorToSave();

				cLigne = parser.PARGetAttribut();

				if (!compareDeuxChaine(cLigne, "Numero"))
					throw CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

				uiVar = atoi(parser.PARGetValeur());
				grapheTempo.GRAAjouterSommet(uiVar);
			}
		}
	}

	cLigne = parser.PARGetValeur();

	test = true;

	parser.PARSaveCursorInFile();
	cLigne = parser.PARGetValeur();
	if (!compareDeuxChaine(cLigne, "]"))
	{
		parser.PARPlaceCursorToSave();

		while (test)
		{
			parser.PARSaveCursorInFile();
			cLigne = parser.PARGetValeur();

			if (compareDeuxChaine(cLigne, "]"))
			{
				test = false;
			}
			else
			{
				parser.PARPlaceCursorToSave();

				cLigne = parser.PARGetAttribut();

				if (!compareDeuxChaine(cLigne, "Debut"))
					throw CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

				cLigne = parser.PARGetValeurJusque(',');
				uiSommetDepart = atoi(cLigne);

				cLigne = parser.PARGetAttribut();
				if (!compareDeuxChaine(cLigne, "Fin"))
					throw CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

				cLigne = parser.PARGetValeur();
				uiSommetArrivee = atoi(cLigne);

				grapheTempo.GRARelierSommets(uiSommetDepart, uiSommetArrivee);
			}
		}
	}

	uiGRANbSommet = grapheTempo.GRALireNbSommet();
	uiGRANbArc = grapheTempo.GRALireNbArc();
	uiGRATailleAlloueListe = grapheTempo.GRALireTailleAlloueListe();

	pSOMGRAListeSommet = (CSommet**)malloc(sizeof(CSommet*) * uiGRATailleAlloueListe);

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		CSommet *sommet = new CSommet(*grapheTempo.GRALireListeSommet(uiBoucle));
		pSOMGRAListeSommet[uiBoucle] = sommet;
	}
}


/***
**** Nom:			~CGraphe
****
**** Description:	Destructeur de la classe
****
**** Precondition:
**** Entree:
**** Entraine:		Desalloue le tableau de l'objet CGraphe avant sa destruction
**** Sortie:
***/
CGraphe::~CGraphe()
{
	unsigned int uiBoucle = 0;

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		delete pSOMGRAListeSommet[uiBoucle];
	}
	free(pSOMGRAListeSommet);
}

/***
**** Nom:			GRAAfficherGraphe
****
**** Description:	Cette méthode affiche le graphe sur la console
****
**** Precondition:
**** Entree:
**** Entraine:		Affichage du graphe sur la console
**** Sortie:
***/
void CGraphe::GRAAfficherGraphe()
{
	unsigned int uiBoucle = 0;
	unsigned int uiBoucle2 = 0;

	if (uiGRANbSommet == 0)
		throw CException(GrapheVide, "Impossible d'afficher le graphe car il est vide");

	std::cout << "Liste des sommets : [";

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet - 1; uiBoucle++)
	{
		std::cout << pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() << ",";
	}
	std::cout << pSOMGRAListeSommet[uiGRANbSommet - 1]->SOMLireNumero() << "]" << std::endl;

	std::cout << "Liste des arc : [";

	if (uiGRANbArc != 0)
	{
		for (uiBoucle = 0; uiBoucle < uiGRANbSommet - 1; uiBoucle++)
		{
			if (pSOMGRAListeSommet[uiBoucle]->SOMLireNbArrivant() != 0)
			{
				for (uiBoucle2 = 0; uiBoucle2 < pSOMGRAListeSommet[uiBoucle]->SOMLireNbArrivant(); uiBoucle2++)
					std::cout << "(" << pSOMGRAListeSommet[uiBoucle]->SOMLireArrivant(uiBoucle2)->ARCLireDestination() << "," << pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() << "),";
			}
		}
		if (pSOMGRAListeSommet[uiBoucle]->SOMLireNbArrivant() != 0)
		{
			for (uiBoucle2 = 0; uiBoucle2 < pSOMGRAListeSommet[uiGRANbSommet - 1]->SOMLireNbArrivant() - 1; uiBoucle2++)
				std::cout << "(" << pSOMGRAListeSommet[uiGRANbSommet - 1]->SOMLireArrivant(uiBoucle2)->ARCLireDestination() << "," << pSOMGRAListeSommet[uiGRANbSommet - 1]->SOMLireNumero() << "),";

			std::cout << "(" << pSOMGRAListeSommet[uiGRANbSommet - 1]->SOMLireArrivant(pSOMGRAListeSommet[uiGRANbSommet - 1]->SOMLireNbArrivant() - 1)->ARCLireDestination() << "," << pSOMGRAListeSommet[uiGRANbSommet - 1]->SOMLireNumero() << ")";
		}
	}
	std::cout << "]" << std::endl;
}

/***
**** Nom:			GRAAjouterSommet
****
**** Description:	Cette méthode ajoute un sommet dans un graphe
****
**** Precondition:
**** Entree:		unsigned int uiNumero
**** Entraine:		Le sommet est ajoute dans le graphe avec commme numero celui passe en parametre
**** Sortie:
***/
void CGraphe::GRAAjouterSommet(unsigned int uiNumero)
{
	unsigned int uiBoucle = 0;
	bool bNumeroTrouve = true;

	if (uiNumero == 0)
	{
		while (bNumeroTrouve)
		{
			uiNumero++;
			bNumeroTrouve = false;

			for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
			{
				if (pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() == uiNumero)
					bNumeroTrouve = true;
			}
		}

	}
	else
	{

		for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
		{
			if (pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() == uiNumero)
				throw CException(NumeroPris, "NUMERO SOMMET DEJA PRIS");
		}
	}

	if (uiGRANbSommet == 0)
		pSOMGRAListeSommet[0] = new CSommet(uiNumero);
	else if (uiGRATailleAlloueListe > uiGRANbSommet)
	{
		pSOMGRAListeSommet[uiGRANbSommet] = new CSommet(uiNumero);
	}
	else if (uiGRATailleAlloueListe <= uiGRANbSommet)
	{
		pSOMGRAListeSommet = (CSommet**)realloc(pSOMGRAListeSommet, (uiGRATailleAlloueListe + 1) * sizeof(CSommet*));
		uiGRATailleAlloueListe++;
		pSOMGRAListeSommet[uiGRANbSommet] = new CSommet(uiNumero);
	}

	uiGRANbSommet++;

}

/***
**** Nom:			GRARelierSommets
****
**** Description:	Cette méthode creer un arc entre deux sommets
****
**** Precondition:
**** Entree:		unsigned int uiSommetDepart, unsigned int uiSommetArriver
**** Entraine:		Un arc a ete cree entre les deux sommmets
**** Sortie:
***/
void CGraphe::GRARelierSommets(unsigned int uiSommetDepart, unsigned int uiSommetArriver)
{
	unsigned int uiBoucle = 0;
	int sommetDepart = -1;
	int sommetArriver = -1;

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		if (pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() == uiSommetDepart)
			sommetDepart = uiBoucle;
	}

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		if (pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() == uiSommetArriver)
			sommetArriver = uiBoucle;
	}

	if (sommetDepart == -1 || sommetArriver == -1)
	{
		throw CException(SommetIntrouvable, "Un des sommet n'est pas dans le graphe");
	}

	if (!(pSOMGRAListeSommet[sommetDepart]->SOMArcPartantPresent(uiSommetArriver)))
	{
		pSOMGRAListeSommet[sommetDepart]->SOMAjouterPartant(uiSommetArriver);
	}

	if (!(pSOMGRAListeSommet[sommetArriver]->SOMArcArrivantPresent(uiSommetDepart)))
	{
		pSOMGRAListeSommet[sommetArriver]->SOMAjouterArrivant(uiSommetDepart);
	}

	uiGRANbArc++;
}

/***
**** Nom:			GRADelierSommets
****
**** Description:	Cette méthode supprimer un arc entre deux sommets
****
**** Precondition:
**** Entree:		unsigned int uiSommetDepart, unsigned int uiSommetArriver
**** Entraine:		Un arc a ete supprime entre les deux sommmets
**** Sortie:
***/
void CGraphe::GRADelierSommets(unsigned int uiSommetDepart, unsigned int uiSommetArriver)
{
	unsigned int uiBoucle = 0;
	int sommetDepart = -1;
	int sommetArriver = -1;

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		if (pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() == uiSommetDepart)
			sommetDepart = uiBoucle;
	}

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		if (pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() == uiSommetArriver)
			sommetArriver = uiBoucle;
	}

	if (sommetDepart == -1 || sommetArriver == -1)
	{
		throw CException(SommetIntrouvable, "Un des sommet n'est pas dans le graphe");
	}

	if (this->GRATrouverSommet(uiSommetArriver)->SOMArcArrivantPresent(uiSommetDepart) || this->GRATrouverSommet(uiSommetDepart)->SOMArcPartantPresent(uiSommetArriver))
	{
		pSOMGRAListeSommet[sommetDepart]->SOMSupprimerPartant(uiSommetArriver);
		pSOMGRAListeSommet[sommetArriver]->SOMSupprimerArrivant(uiSommetDepart);
		uiGRANbArc--;
	}
}

/***
**** Nom:			GRASupprimerGraphe
****
**** Description:	Cette méthode supprime le graphe
****
**** Precondition:
**** Entree:
**** Entraine:		Suppression du graphe
**** Sortie:
***/
void CGraphe::GRASupprimerGraphe()
{
	unsigned int uiBoucle = 0;
	unsigned int uiNbSommetCopie = uiGRANbSommet;

	for (uiBoucle = 0; uiBoucle < uiNbSommetCopie; uiBoucle++)
		this->GRASupprimerSommet(pSOMGRAListeSommet[uiBoucle]->SOMLireNumero());
}

/***
**** Nom:			GRASupprimerSommet
****
**** Description:	Cette méthode supprime du graphe le sommet dont le numero est passe en parametre
****
**** Precondition:
**** Entree:		unsigned int uiSommet
**** Entraine:		Suppression du sommet
**** Sortie:
***/
void CGraphe::GRASupprimerSommet(unsigned int uiSommet)
{
	unsigned int uiBoucle = 0;

	if (uiGRANbSommet == 1)
	{
		delete pSOMGRAListeSommet[0];
	}
	else
	{
		for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
		{
			this->GRADelierSommets(uiSommet, pSOMGRAListeSommet[uiBoucle]->SOMLireNumero());
		}

		for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
		{
			this->GRADelierSommets(pSOMGRAListeSommet[uiBoucle]->SOMLireNumero(), uiSommet);
		}

		bool bTrouvee = false;
		for (uiBoucle = 0; uiBoucle < uiGRANbSommet - 1; uiBoucle++)
		{
			if (bTrouvee == false && pSOMGRAListeSommet[uiBoucle]->SOMLireNumero() == uiSommet)
			{
				bTrouvee = true;
				delete pSOMGRAListeSommet[uiBoucle];
			}
			if (bTrouvee)
			{
				pSOMGRAListeSommet[uiBoucle] = pSOMGRAListeSommet[uiBoucle + 1];
			}
		}
	}

	uiGRANbSommet--;
}

/***
**** Nom:			GRALireNbSommet
****
**** Description:	Cette méthode renvoit la nombre de sommet du graphe
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de l'attibut uiGRANbSommet
**** Sortie:		unsigned int
***/
unsigned int CGraphe::GRALireNbSommet()
{
	return uiGRANbSommet;
}

/***
**** Nom:			GRALireNbArc
****
**** Description:	Cette méthode renvoit la nombre d'arc du graphe
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de l'attibut uiGRANbArc
**** Sortie:		unsigned int
***/
unsigned int CGraphe::GRALireNbArc()
{
	return uiGRANbArc;
}

/***
**** Nom:			GRALireTailleAlloueListe
****
**** Description:	Cette méthode renvoit la taille alloue a la liste de sommet
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de l'attibut uiGRATailleAlloueListe
**** Sortie:		unsigned int
***/
unsigned int CGraphe::GRALireTailleAlloueListe()
{
	return uiGRATailleAlloueListe;
}

/***
**** Nom:			GRALireListeSommet
****
**** Description:	Cette méthode renvoit l'addresse de l'objet sommet à la position donnee
****
**** Precondition:
**** Entree:		unsigned int uiPosition
**** Entraine:		Renvoit le CSommet à la position passee en parametre de la liste de sommet
**** Sortie:		CSommet*
***/
CSommet* CGraphe::GRALireListeSommet(unsigned int uiPosition)
{
	return pSOMGRAListeSommet[uiPosition];
}

/***
**** Nom:			GRATrouverSommet
****
**** Description:	Cette méthode renvoit l'adresse du sommet ayant comme numero uiSommet
****
**** Precondition:
**** Entree:		unsigned int uiSommet
**** Entraine:		Renvoit l'adresse du sommet ayant comme numero uiSommet placee en parametre
**** Sortie:		CSommet*
***/
CSommet * CGraphe::GRATrouverSommet(unsigned int uiSommet)
{
	unsigned int uiBoucle = 0;

	for (uiBoucle = 0; uiBoucle < this->GRALireNbSommet(); uiBoucle++)
	{
		if (this->GRALireListeSommet(uiBoucle)->SOMLireNumero() == uiSommet)
			return this->GRALireListeSommet(uiBoucle);
	}

	throw new CException(SommetIntrouvable, "Le sommet n'est pas dans le graphe");
}

CGraphe CGraphe::GRAInverserGraphe()
{
	unsigned int uiBoucle = 0;
	unsigned int uiSave = 0;

	CGraphe GRARetour(*this);

	for (uiBoucle = 0; uiBoucle < GRARetour.GRALireNbSommet(); uiBoucle++)
	{
		CArc ** pARCSaveArrivant = GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMLireListeArrivant();
		CArc ** pARCSavePartant = GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMLireListePartant();

		GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMModifierListeArrivant(pARCSavePartant);
		GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMModifierListePartant(pARCSaveArrivant);

		uiSave = GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMLireNbArrivant();

		GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMModifierNbArrivant(GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMLireNbPartant());
		GRARetour.pSOMGRAListeSommet[uiBoucle]->SOMModifierNbPartant(uiSave);
	}


	return GRARetour;
}

CGraphe & CGraphe::operator=(CGraphe & GRAGraphe)
{
	unsigned int uiBoucle = 0;

	if (pSOMGRAListeSommet != nullptr)
	{
		for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
		{
			delete pSOMGRAListeSommet[uiBoucle];
		}
		free(pSOMGRAListeSommet);
	}

	uiGRANbArc = GRAGraphe.uiGRANbArc;
	uiGRANbSommet = GRAGraphe.uiGRANbSommet;
	uiGRATailleAlloueListe = GRAGraphe.uiGRATailleAlloueListe;

	pSOMGRAListeSommet = (CSommet**)malloc(sizeof(CSommet*) * uiGRATailleAlloueListe);

	for (uiBoucle = 0; uiBoucle < uiGRANbSommet; uiBoucle++)
	{
		pSOMGRAListeSommet[uiBoucle] = new CSommet(*GRAGraphe.GRALireListeSommet(uiBoucle));
	}

	return *this;
}
