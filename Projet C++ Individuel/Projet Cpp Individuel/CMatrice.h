#ifndef CMatrice_h
#define CMatrice_h

#include "CException.h"

template <class T> class CMatrice
{
private:
	unsigned int uiMATNbLigne; 
	unsigned int uiMATNbColonne; 
	T** pTMATMatrice;

public:
	//Constructeur
	CMatrice<T>();
	CMatrice<T>(unsigned int uiNbLigne, unsigned int uiNbColonne);
	CMatrice<T>(CMatrice& Matrice);
	CMatrice<T>(CMatrice&& Matrice);
	CMatrice<T>(const char* pcCheminAcces);
	~CMatrice<T>();

	//Accesseurs
	unsigned int MATLireNbLigne();
	unsigned int MATLireNbColonne();

	//Methodes
	void MATAfficher();
	void MATAjouter(T Telement, unsigned int uiLigne, unsigned int uiColonne);
	T MATLireElement(unsigned int uiLigne, unsigned int uiColonne);
	CMatrice& operator=(CMatrice& MATMatrice);
	CMatrice& operator=(CMatrice&& MATMatrice);
	CMatrice operator/(double dConstante);
	T& operator()(unsigned int uiLigne, unsigned int uiColonne);
};

/***
**** Nom:			operator*
****
**** Description:	Surcharge operateur * avec une constante à gauche
****
**** Prcondition:	Il faut que le type T est une surcharge de l'operateur * avec une constante à gauche
**** Entree:		double dConstante, CMatrice<T> MATMatrice
**** Entraine:		Le renvoit de la multiplication de la matrice par la constante à gauche
**** Sortie:		CMatrice<T>
***/

template <class T>
CMatrice<T> operator*(double dConstante, CMatrice<T> MATMatrice) {

	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	CMatrice<T> MATTemporaire(MATMatrice);
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < MATMatrice.MATLireNbLigne(); uiBoucleAxeLigne++)
	{
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < MATMatrice.MATLireNbColonne(); uiBoucleAxeColonne++)
		{
			MATTemporaire.MATAjouter((dConstante * MATMatrice.MATLireElement(uiBoucleAxeLigne, uiBoucleAxeColonne)), uiBoucleAxeLigne, uiBoucleAxeColonne);
		}
	}
	return MATTemporaire;
}

/***
**** Nom:			operator*
****
**** Description:	Surcharge operateur * avec une constante à droite
****
**** Prcondition:	Il faut que le type T est une surcharge de l'operateur * avec une constante à droite
**** Entree:		CMatrice<T> MATMatrice, double dConstante
**** Entraine:		Le renvoit de la multiplication de la matrice par la constante à droite
**** Sortie:		CMatrice<T>
***/

template <class T>
CMatrice<T> operator*(CMatrice<T> MATMatrice, double dConstante) {

	unsigned int uiBoucleAxeLigne = 0;
	unsigned int uiBoucleAxeColonne = 0;

	CMatrice<T> MATTemporaire(MATMatrice);
	for (uiBoucleAxeLigne = 0; uiBoucleAxeLigne < MATMatrice.MATLireNbLigne(); uiBoucleAxeLigne++)
	{
		for (uiBoucleAxeColonne = 0; uiBoucleAxeColonne < MATMatrice.MATLireNbColonne(); uiBoucleAxeColonne++)
		{
			MATTemporaire.MATAjouter((MATMatrice.MATLireElement(uiBoucleAxeLigne, uiBoucleAxeColonne)*dConstante), uiBoucleAxeLigne, uiBoucleAxeColonne);
		}
	}
	return MATTemporaire;
}

#include "CMatrice.cpp"

#endif
