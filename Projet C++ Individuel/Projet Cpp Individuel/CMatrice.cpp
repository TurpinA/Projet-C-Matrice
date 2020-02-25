#include <iostream>
#include "CMatrice.h"
#include "CParser.h"

//Exception List
#define ErreurMathematique 100
#define OutOfDimension 101
#define InvalidArgument 12
#define FormatIncorrect 11
#define ErreurFichier 10

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

	int iParcoureur = 0, verifTailleChaine1 = 0, verifTailleChaine2 = 0;


	//On passe les espaces en trop devant la chaine de caractere
	while (*pcChaine1 == ' ' || *pcChaine1 == '\n')
	{
		pcChaine1++;
	}

	//On verifie si les chaines de caractere ont la meme taille
	while (pcChaine1[iParcoureur] != '\0')
	{
		iParcoureur++;
		verifTailleChaine1++;
	}

	iParcoureur = 0;

	while (pcChaine2[iParcoureur] != '\0')
	{
		iParcoureur++;
		verifTailleChaine2++;
	}

	iParcoureur = 0;

	if (verifTailleChaine1 != verifTailleChaine2)
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
**** Nom:			CMatrice
****
**** Description:	Constructeur par defaut
****
**** Precondition:
**** Entree:
**** Entraine:		Attributs tous à nul
**** Sortie:
***/

template<class T>
CMatrice<T>::CMatrice()
{
	uiMATNbColonne = 0;
	uiMATNbLigne = 0;
	pTMATMatrice = nullptr;
}

/***
**** Nom:			CMatrice
****
**** Description:	Constructeur de confort
****
**** Precondition:
**** Entree:		unsigned int uiNbLigne, unsigned int uiNbColonne
**** Entraine:		Creation du tableau d'objet
**** Sortie:
***/

template <class T>
CMatrice<T>::CMatrice(unsigned int uiNbLigne, unsigned int uiNbColonne)
{
	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	uiMATNbLigne = uiNbLigne;
	uiMATNbColonne = uiNbColonne;

	pTMATMatrice = new T*[uiMATNbLigne];
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		pTMATMatrice[uiBoucleAxeLigne] = new T[uiMATNbColonne];
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
		{
			pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne] = T();
		}
	}

}

/***
**** Nom:			CMatrice
****
**** Description:	Constructeur de recopie avec un objet par reference  gauche
****
**** Precondition:
**** Entree:		CMatrice & Matrice
**** Entraine:		Creation du tableau de l'objet avec appelle au constructeur de recopie de l'objet
**** Sortie:
***/

template<class T>
CMatrice<T>::CMatrice(CMatrice & MATMatrice)
{
	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	uiMATNbColonne = MATMatrice.uiMATNbColonne;
	uiMATNbLigne = MATMatrice.uiMATNbLigne;

	pTMATMatrice = new T*[uiMATNbLigne];
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		pTMATMatrice[uiBoucleAxeLigne] = new T[uiMATNbColonne];
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
		{
			pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne] = T((MATMatrice.pTMATMatrice)[uiBoucleAxeLigne][uiBoucleAxeColonne]);
		}
	}
}

/***
**** Nom:			CMatrice
****
**** Description:	Constructeur de recopie avec un objet par reference  droite
****
**** Precondition:
**** Entree:		CMatrice && Matrice
**** Entraine:		Creation du tableau de l'objet avec appelle au constructeur de recopie de l'objet
**** Sortie:
***/

template<class T>
CMatrice<T>::CMatrice(CMatrice&& MATMatrice)
{
	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	uiMATNbColonne = MATMatrice.uiMATNbColonne;
	uiMATNbLigne = MATMatrice.uiMATNbLigne;

	pTMATMatrice = new T *[uiMATNbLigne];
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		pTMATMatrice[uiBoucleAxeLigne] = new T[uiMATNbColonne];
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
		{
			pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne] = T((MATMatrice.pTMATMatrice)[uiBoucleAxeLigne][uiBoucleAxeColonne]);
		}
	}
}

/***
**** Nom:			CMatrice
****
**** Description:	Constructeur de confort
****
**** Precondition:
**** Entree:		const char* pcCheminAcces
**** Entraine:		Appel de la methode CParseur::ParseurFichierAMatrice(char* pcCheminAcces)
****				Construction de l'objet
**** Sortie:
***/

template<class T>
CMatrice<T>::CMatrice(const char * pcCheminAcces)
{
	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;
	unsigned int uiBoucle1 = 0;
	unsigned int uiBoucle2 = 0;

	CParser parser(pcCheminAcces);

	char *cTypeMatrice;
	unsigned int uiNbligne = 0;
	unsigned int uiNbcol = 0;

	char *cLigne;

	double dNbcolVerif = 0;
	double dNbligneVerif = 0;

	cLigne = parser.PARGetAttribut();

	if (!compareDeuxChaine(cLigne, "TypeMatrice"))
		throw CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	cTypeMatrice = parser.PARGetValeurLine();

	if (!compareDeuxChaine(cTypeMatrice, "double"))
		throw  CException(FormatIncorrect, "ERREUR DE TYPE SEULEMENT DOUBLE ACCEPTEE");

	cLigne = parser.PARGetAttribut();

	if (!compareDeuxChaine(cLigne, "NBLignes"))
		throw  CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	cLigne = parser.PARGetValeurLine();
	uiNbligne = atoi(cLigne);

	cLigne = parser.PARGetAttribut();

	if (!compareDeuxChaine(cLigne, "NBColonnes"))
		throw  CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	cLigne = parser.PARGetValeurLine();
	uiNbcol = atoi(cLigne);

	cLigne = parser.PARGetValeurLine();
	if (!compareDeuxChaine(cLigne, "Matrice=["))
		throw  CException(FormatIncorrect, "ERREUR DE FORMAT DU FICHIER");

	//SAVE CURSOR IN FILE
	parser.PARSaveCursorInFile();

	//COMPTAGE DE LIGNES
	cLigne = parser.PARGetValeurLine();
	while (!compareDeuxChaine(cLigne, "]"))
	{
		if(!compareDeuxChaine(cLigne, ""))
			dNbligneVerif++;

		cLigne = parser.PARGetValeurLine();
	}

	//COMPTAGE DE COLONNES
	parser.PARPlaceCursorToSave();

	cLigne = parser.PARGetValeur();
	while (!compareDeuxChaine(cLigne, "]"))
	{
		dNbcolVerif++;
		cLigne = parser.PARGetValeur();
	}

	dNbcolVerif /= dNbligneVerif;

	//VERIF DIMENSION DONNEES ET MATRICE
	if (uiNbcol != dNbcolVerif || uiNbligne != dNbligneVerif)
		throw  CException(InvalidArgument, "INCOHERENCES ARGUMENTS");

	//On remet le curseur aprs le Matrice=[
	parser.PARPlaceCursorToSave();

	//CREATION MATRICE
	CMatrice<double> MATMatrice(uiNbligne, uiNbcol);
	double dVar = 0;

	for (uiBoucle1 = 0; uiBoucle1 < uiNbligne; uiBoucle1++)
	{
		for (uiBoucle2 = 0; uiBoucle2 < uiNbcol; uiBoucle2++)
		{
			cLigne = parser.PARGetValeur();
			dVar = atof(cLigne);
			MATMatrice(uiBoucle1, uiBoucle2) = dVar;
		}
	}

	uiMATNbColonne = MATMatrice.uiMATNbColonne;
	uiMATNbLigne = MATMatrice.uiMATNbLigne;

	pTMATMatrice = new T *[uiMATNbLigne];
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		pTMATMatrice[uiBoucleAxeLigne] = new T[uiMATNbColonne];
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
		{
			pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne] = T((MATMatrice.pTMATMatrice)[uiBoucleAxeLigne][uiBoucleAxeColonne]);
		}
	}
}

/***
**** Nom:			~CMatrice
****
**** Description:	Destructeur
****
**** Precondition:
**** Entree:
**** Entraine:		Destruction des tableaux avec appel aux destructeurs de chaque objets
**** Sortie:
***/

template <class T>
CMatrice<T>::~CMatrice()
{
	unsigned int uiBoucleAxeLigne = 0;

	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		delete pTMATMatrice[uiBoucleAxeLigne];
	}
	delete pTMATMatrice;
}

/***
**** Nom:			MATLireNbLigne
****
**** Description:	Accesseurs en lecture uiMATNbLigne
****
**** Precondition:
**** Entree:
**** Entraine:		retour du nombre de ligne de l'objet
**** Sortie:		unsigned int
***/

template<class T>
unsigned int CMatrice<T>::MATLireNbLigne()
{
	return uiMATNbLigne;
}

/***
**** Nom:			MATLireNbColonne
****
**** Description:	Accesseurs en lecture uiMATNbColonne
****
**** Precondition:
**** Entree:
**** Entraine:		retour du nombre de colonne de l'objet
**** Sortie:		unsigned int
***/

template<class T>
unsigned int CMatrice<T>::MATLireNbColonne()
{
	return uiMATNbColonne;
}

/***
**** Nom:			MATAfficher
****
**** Description:	Afficher la matrice
****
**** Precondition:
**** Entree:
**** Entraine:		Affiche la matrice
**** Sortie:
***/
template<class T>
void CMatrice<T>::MATAfficher()
{
	std::cout << "Affichage de la matrice" << std::endl;

	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		std::cout << "\t";
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
		{
			std::cout << pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne];
			std::cout << "\t";
		}
		std::cout << " " << std::endl;
	}
}

/***
**** Nom:			MATAjouter
****
**** Description:	Ajoute un objet
****
**** Precondition:
**** Entree:		T Telement, unsigned int uiLigne, unsigned int uiColonne
**** Entraine:		Ajoute un objet  la position indiquee
**** Sortie:
***/

template<class T>
void CMatrice<T>::MATAjouter(T Telement, unsigned int uiLigne, unsigned int uiColonne)
{
	if (uiLigne > uiLigne)
		throw CException(OutOfDimension, "Hors dimension de la matrice");
	if (uiColonne > uiMATNbColonne)
		throw CException(OutOfDimension, "Hors dimension de la matrice");

	pTMATMatrice[uiLigne][uiColonne] = Telement;
}

/***
**** Nom:			MATLireElement
****
**** Description:	Lis l'element  la position indiquee en parametre
****
**** Precondition:
**** Entree:		unsigned int uiLigne, unsigned int uiColonne
**** Entraine:		retour une copie de l'element
**** Sortie:		T
***/

template<class T>
T CMatrice<T>::MATLireElement(unsigned int uiLigne, unsigned int uiColonne)
{
	if (uiLigne > uiLigne)
		throw CException(OutOfDimension, "Hors dimension de la matrice");
	if (uiColonne > uiMATNbColonne)
		throw CException(OutOfDimension, "Hors dimension de la matrice");

	return pTMATMatrice[uiLigne][uiColonne];
}

/***
**** Nom:			operator=
****
**** Description:	Permet d'assigner l'ancien objet avec le nouvel objet en parametre par reference  gauche
****
**** Precondition:
**** Entree:		CMatrice<T> & MATMatrice
**** Entraine:		Suppression des anciens pointeurs de tableau
****				Recupration des tailles du tableau
****				Ajout des nouvelles valeurs dans le tableau par appel au constructeur de recopie
**** Sortie:		CMatrice<T> & MATMatrice
***/

template<class T>
CMatrice<T> & CMatrice<T>::operator=(CMatrice<T> & MATMatrice)
{
	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	if (this != &MATMatrice)
	{
		if (pTMATMatrice != nullptr)
		{
			for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
			{
				delete pTMATMatrice[uiBoucleAxeLigne];
			}
			delete pTMATMatrice;
		}

		this->uiMATNbColonne = MATMatrice.uiMATNbColonne;
		this->uiMATNbLigne = MATMatrice.uiMATNbLigne;

		pTMATMatrice = new T*[uiMATNbLigne];
		for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
		{
			pTMATMatrice[uiBoucleAxeLigne] = new T[uiMATNbColonne];
			for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
			{
				pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne] = T((MATMatrice.pTMATMatrice)[uiBoucleAxeLigne][uiBoucleAxeColonne]);
			}
		}
	}


	return *this;
}

/***
**** Nom:			operator=
****
**** Description:	Permet d'assigner l'ancien objet avec le nouvel objet en parametre par reference  droite
****
**** Precondition:
**** Entree:		CMatrice<T> && MATMatrice
**** Entraine:		Suppression des anciens pointeurs de tableau
****				Recupration des tailles du tableau
****				Ajout des nouvelles valeurs dans le tableau par appel au constructeur de recopie
**** Sortie:		CMatrice<T> & MATMatrice
***/

template<class T>
CMatrice<T> & CMatrice<T>::operator=(CMatrice<T>&& MATMatrice)
{
	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	if (pTMATMatrice != nullptr)
	{
		for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
		{
			delete pTMATMatrice[uiBoucleAxeLigne];
		}
		delete pTMATMatrice;
	}

	this->uiMATNbColonne = MATMatrice.uiMATNbColonne;
	this->uiMATNbLigne = MATMatrice.uiMATNbLigne;

	pTMATMatrice = new T *[uiMATNbLigne];
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		pTMATMatrice[uiBoucleAxeLigne] = new T[uiMATNbColonne];
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
		{
			pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne] = T((MATMatrice.pTMATMatrice)[uiBoucleAxeLigne][uiBoucleAxeColonne]);
		}
	}

	return *this;
}

/***
**** Nom:			operator/
****
**** Description:	Surcharge de l'oprateur /, permet la division de chaque elements par celui en parametre
****
**** Precondition:	Avertissement, perte de donne possible en fonction de l'utilisation de la methode
**** Entree:		double dConstante
**** Entraine:		Affiche la matrice
**** Sortie:		CMatrice<T>
***/

template<class T>
CMatrice<T> CMatrice<T>::operator/(double dConstante)
{
	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	if (dConstante == 0)
		throw CException(ErreurMathematique, "Divison par 0");

	CMatrice<T> MATTemporaire(*this);
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < uiMATNbLigne; uiBoucleAxeLigne++)
	{
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < uiMATNbColonne; uiBoucleAxeColonne++)
		{
			MATTemporaire.pTMATMatrice[uiBoucleAxeLigne][uiBoucleAxeColonne] /= dConstante;
		}
	}
	return MATTemporaire;

}

/***
**** Nom:			operator()
****
**** Description:	retourne l'element  la position indiquee en parametre par reference
****
**** Precondition:
**** Entree:		unsigned int uiLigne, unsigned int uiColonne
**** Entraine:		retourne l'element  la position en parametre
**** Sortie:		T&
***/

template<class T>
T& CMatrice<T>::operator()(unsigned int uiLigne, unsigned int uiColonne)
{
	if (uiLigne > uiLigne)
		throw CException(OutOfDimension, "Hors dimension de la matrice");
	if (uiColonne > uiMATNbColonne)
		throw CException(OutOfDimension, "Hors dimension de la matrice");

	return pTMATMatrice[uiLigne][uiColonne];
}







