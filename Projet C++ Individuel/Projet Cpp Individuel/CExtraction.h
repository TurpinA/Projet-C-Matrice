#ifndef CEXTRACTION_h
#define CEXTRACTION_h

//Include
#include "CMatrice.h"

class CExtraction
{
public:

	//Methodes
	template <class T>
	CMatrice<T> EXTExtractionPointOrigine(CMatrice<T> MATMatrice,unsigned int uiCoordi, unsigned int uiCoordj, unsigned int uiNbColonne, unsigned int uiNbLigne);

	template <class T>
	CMatrice<T> EXTExtractionPointCentrale(CMatrice<T> MATMatrice, unsigned int uiCoordi, unsigned int uiCoordj, unsigned int uiNbColonne, unsigned int uiNbLigne);
	
	template <class T>
	CMatrice<T>** EXTExtractionCompleteMatriceCarree(CMatrice<T> MATMatrice, unsigned int uiTaille);
};

#include "CExtraction.cpp"

#endif // !CEXTRACTION_h
