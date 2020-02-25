#ifndef CMatriceOperationComplexe_h
#define	CMatriceOperationComplexe_h

//Exception List
#define ErreurMathematique 100

//Include
#include "CMatrice.h"



class CMatriceOperationComplexe
{
public:
	template <class T>
	CMatrice<T> MOCTranspose(CMatrice<T> MATMatrice);
};

/***
**** Nom:			operator*                                            
****
**** Description:	Cette fonction renvoit la matrice correspondant à la multiplication des matrices placées en paramètre.                              
****
**** Precondition:	Les types M et T  doivent avoir une surcharge de l'opérateur *                                           
**** Entree:		CMatrice<T> MATMatriceGauche, CMatrice<M> MATMatriceDroite
**** Entraine:		Le renvoit de la multiplication des deux matrices                                    
**** Sortie:        Indeterminé                                          
***/

template <class T,class M>
auto operator*(CMatrice<T> MATMatriceGauche, CMatrice<M> MATMatriceDroite) 
{
	unsigned int AxeLigne = 0;
	unsigned int AxeColonne = 0;
	unsigned int AxeInverse = 0;

	if (MATMatriceGauche.MATLireNbColonne() != MATMatriceDroite.MATLireNbLigne())
	{
		throw CException(ErreurMathematique,"Impossible de multiplier erreur de dimension");
	}

	CMatrice<decltype(MATMatriceGauche(0, 0) + MATMatriceDroite(0, 0))> MATMatriceTempo(MATMatriceGauche.MATLireNbLigne(), MATMatriceDroite.MATLireNbColonne());
	
	for (AxeLigne = 0; AxeLigne < MATMatriceGauche.MATLireNbColonne(); AxeLigne++)
	{
		for (AxeColonne = 0; AxeColonne < MATMatriceDroite.MATLireNbLigne(); AxeColonne++)
		{
			for (AxeInverse = 0; AxeInverse < MATMatriceGauche.MATLireNbColonne(); AxeInverse++)
			{
				MATMatriceTempo(AxeLigne, AxeColonne) += (MATMatriceGauche(AxeLigne, AxeInverse) * MATMatriceDroite(AxeInverse, AxeColonne));
			}
		}
	}

	return MATMatriceTempo;
}

/***
**** Nom:			operator+                                            
****
**** Description:	Cette fonction renvoit la matrice correspondant à l'addition des matrices placées en paramètre.                              
****
**** Precondition:	Les types M et T  doivent avoir une surcharge de l'opérateur +                                           
**** Entree:		CMatrice<T> MATMatriceGauche, CMatrice<M> MATMatriceDroite
**** Entraine:		Le renvoit de l'addition des deux matrices                                    
**** Sortie:        Indeterminé                                          
***/

template <class T, class M>
auto operator+(CMatrice<T> MATMatriceGauche, CMatrice<M> MATMatriceDroite) 
{
	unsigned int AxeLigne = 0;
	unsigned int AxeColonne = 0;

	if (MATMatriceGauche.MATLireNbColonne() != MATMatriceDroite.MATLireNbColonne() || MATMatriceGauche.MATLireNbLigne() != MATMatriceDroite.MATLireNbLigne())
	{
		throw CException(ErreurMathematique, "Impossible d'additionner erreur de dimension");
	}

	CMatrice<decltype(MATMatriceGauche(0,0)+ MATMatriceDroite(0,0))> MATMatriceTempo(MATMatriceGauche.MATLireNbLigne(), MATMatriceDroite.MATLireNbColonne());

	for (AxeLigne = 0; AxeLigne < MATMatriceGauche.MATLireNbLigne(); AxeLigne++)
	{
		for (AxeColonne = 0; AxeColonne < MATMatriceDroite.MATLireNbColonne(); AxeColonne++)
		{
			MATMatriceTempo(AxeLigne, AxeColonne) = MATMatriceGauche(AxeLigne, AxeColonne) + MATMatriceDroite(AxeLigne, AxeColonne);
		}
	}
	return MATMatriceTempo;
}

/***
**** Nom:			operator-                                            
****
**** Description:	Cette fonction renvoit la matrice correspondant à la soustraction des matrices placées en paramètre.                              
****
**** Precondition:	Les types M et T  doivent avoir une surcharge de l'opérateur -                                           
**** Entree:		CMatrice<T> MATMatriceGauche, CMatrice<M> MATMatriceDroite
**** Entraine:		Le renvoit de la soustraction des deux matrices                                    
**** Sortie:        Indeterminé                                          
***/

template <class T, class M>
auto operator-(CMatrice<T> MATMatriceGauche, CMatrice<M> MATMatriceDroite) {

	unsigned int AxeLigne = 0;
	unsigned int AxeColonne = 0;

	if (MATMatriceGauche.MATLireNbColonne() != MATMatriceDroite.MATLireNbColonne() || MATMatriceGauche.MATLireNbLigne() != MATMatriceDroite.MATLireNbLigne())
	{
		throw CException(ErreurMathematique, "Impossible de soustraire erreur de dimension");
	}

	CMatrice<decltype(MATMatriceGauche(0, 0) - MATMatriceDroite(0, 0))> MATMatriceTempo(MATMatriceGauche.MATLireNbLigne(), MATMatriceDroite.MATLireNbColonne());

	for (AxeLigne = 0; AxeLigne < MATMatriceGauche.MATLireNbLigne(); AxeLigne++)
	{
		for (AxeColonne = 0; AxeColonne < MATMatriceDroite.MATLireNbColonne(); AxeColonne++)
		{
			MATMatriceTempo(AxeLigne, AxeColonne) = MATMatriceGauche(AxeLigne, AxeColonne) - MATMatriceDroite(AxeLigne, AxeColonne);
		}
	}
	return MATMatriceTempo;
}

#include "CMatriceOperationComplexe.cpp"

#endif

