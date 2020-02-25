/***
**** Nom:			MOCTranspose
****
**** Description:	Cette fonction renvoit la transposée de la matrice placé en paramètre
****
**** Precondition:
**** Entree:		CMatrice<T> MATMatrice
**** Entraine:		Création et renvoit de la transposé de la matrice
**** Sortie:        CMatrice<T>
***/


template<class T>
CMatrice<T> CMatriceOperationComplexe::MOCTranspose(CMatrice<T> MATMatrice)
{
	unsigned int uiAxeLigne = 0;
	unsigned int uiAxeColonne = 0;

	if (MATMatrice.MATLireNbColonne() != MATMatrice.MATLireNbColonne())
	{
		throw CException(ErreurMathematique, "Impossible de transposer erreur de dimension");
	}

	CMatrice<T> MATMatriceTempo(MATMatrice);

	for (uiAxeLigne = 0; uiAxeLigne < MATMatrice.MATLireNbLigne(); uiAxeLigne++)
	{
		for (uiAxeColonne = 0; uiAxeColonne < MATMatrice.MATLireNbColonne(); uiAxeColonne++)
		{
			MATMatriceTempo(uiAxeColonne, uiAxeLigne) = MATMatrice(uiAxeLigne, uiAxeColonne);
		}
	}

	return MATMatriceTempo;
}

