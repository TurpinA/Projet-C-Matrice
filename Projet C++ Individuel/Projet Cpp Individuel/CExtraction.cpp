#include "CExtraction.h"
#include "CExtraction.h"
#include "CMatrice.h"

//Exception Liste
#define OutOfBorn 1110

template<typename T>
CMatrice<T> CExtraction::EXTExtractionPointOrigine(CMatrice<T> MATMatrice, unsigned int uiCoordi, unsigned int uiCoordj, unsigned int uiNbColonne, unsigned int uiNbLigne)
{
	CMatrice<T> MATMatriceResultat(uiNbLigne, uiNbColonne);
	unsigned int uiCoordiBoucle;
	unsigned int uiCoordjBoucle;

	if (uiCoordi >= MATMatrice.MATLireNbLigne() || uiCoordj >= MATMatrice.MATLireNbColonne())
	{
		throw CException(OutOfBorn, "Les coordonnées du points sont en dehors de la matrice");
	}

	if (uiCoordi + uiNbLigne > MATMatrice.MATLireNbLigne() || uiCoordj + uiNbColonne > MATMatrice.MATLireNbColonne())
	{
		throw CException(OutOfBorn, "Les longueurs de la sous matrices dépasse la matrice d'origine");
	}

	for (uiCoordiBoucle = uiCoordi; uiCoordiBoucle < uiCoordi+uiNbLigne; uiCoordiBoucle++)
	{
		for (uiCoordjBoucle = uiCoordj; uiCoordjBoucle < uiCoordj + uiNbColonne; uiCoordjBoucle++) {
			MATMatriceResultat(uiCoordiBoucle - uiCoordi, uiCoordjBoucle - uiCoordj) = MATMatrice(uiCoordiBoucle, uiCoordjBoucle);
		}
	}

	return MATMatriceResultat;
}

template<typename T>
CMatrice<T> CExtraction::EXTExtractionPointCentrale(CMatrice<T> MATMatrice, unsigned int uiCoordi, unsigned int uiCoordj, unsigned int uiNbColonne, unsigned int uiNbLigne)
{
	CMatrice<T> MATMatriceResultat(uiNbLigne*2+1, uiNbColonne*2+1);
	unsigned int uiCoordiBoucle;
	unsigned int uiCoordjBoucle;

	if (uiCoordi >= MATMatrice.MATLireNbLigne() || uiCoordj >= MATMatrice.MATLireNbColonne())
	{
		throw CException(OutOfBorn, "Les coordonnees du points sont en dehors de la matrice");
	}

	if (uiCoordi + uiNbLigne >= MATMatrice.MATLireNbLigne() || uiCoordj + uiNbColonne >= MATMatrice.MATLireNbColonne())
	{
		throw CException(OutOfBorn, "Les longueurs de la sous matrices depasse la matrice d'origine");
	}

	if (uiCoordi - uiNbLigne < 0 || uiCoordj - uiNbColonne < 0)
	{
		throw CException(OutOfBorn, "Les longueurs de la sous matrices depasse la matrice d'origine");
	}

	for (uiCoordiBoucle = uiCoordi - uiNbLigne; uiCoordiBoucle <= uiCoordi + uiNbLigne; uiCoordiBoucle++)
	{
		for (uiCoordjBoucle = uiCoordj - uiNbColonne; uiCoordjBoucle <= uiCoordj + uiNbColonne; uiCoordjBoucle++) {
			MATMatriceResultat(uiCoordiBoucle - (uiCoordi - uiNbLigne), uiCoordjBoucle - (uiCoordj - uiNbColonne)) = MATMatrice(uiCoordiBoucle, uiCoordjBoucle);
		}
	}

	return MATMatriceResultat;
}

template<class T>
CMatrice<T>** CExtraction::EXTExtractionCompleteMatriceCarree(CMatrice<T> MATMatrice, unsigned int uiTaille)
{
	unsigned int uiBoucleLigne;
	unsigned int uiBoucleColonne;
	unsigned int uiBoucleMatrice = 0;
	unsigned int uiNbMatrice;
	CMatrice<T>** pMATTableauMatrice;

	if (uiTaille > MATMatrice.MATLireNbLigne() || uiTaille > MATMatrice.MATLireNbColonne())
	{
		throw CException(OutOfBorn, "Les dimensions depassent la matrice");
	}

	uiNbMatrice = (MATMatrice.MATLireNbLigne() + 1 - uiTaille)*(MATMatrice.MATLireNbColonne() + 1 - uiTaille);
	pMATTableauMatrice = new CMatrice<T>*[uiNbMatrice];
	
	for ( uiBoucleLigne = 0; uiBoucleLigne < MATMatrice.MATLireNbLigne()-uiTaille+1; uiBoucleLigne++)
	{
		for (uiBoucleColonne = 0; uiBoucleColonne < MATMatrice.MATLireNbColonne() - uiTaille+1; uiBoucleColonne++)
		{                                                                                                                                                                                                                                                   
			pMATTableauMatrice[uiBoucleMatrice] = new CMatrice<T>(EXTExtractionPointOrigine(MATMatrice, uiBoucleLigne, uiBoucleColonne, uiTaille, uiTaille));
			uiBoucleMatrice++;
		}
	}
	
	return pMATTableauMatrice;
}


