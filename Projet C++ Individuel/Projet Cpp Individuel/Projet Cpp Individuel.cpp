#include <iostream>
#include "CExtraction.h"
#include "CMatrice.h"

int main(int argc, char *argv[])
{
	CMatrice<double> MATMatrice1;
	CExtraction EXTExtraction;
	CMatrice<double>** pMATTableauMatrice = nullptr;
	unsigned int uiTailleMatrice = 4;

	if (argc == 2)
	{
		MATMatrice1 = CMatrice<double>(argv[1]);
	}
	else
		MATMatrice1 = CMatrice<double>("../test.txt");

	std::cout << "---------------------------------------" << std::endl << std::endl;
	std::cout << "         Matrice        " << std::endl << std::endl;
	try
	{
		MATMatrice1.MATAfficher();
	}
	catch (CException EXCException)
	{
		std::cout << EXCException.EXCLireMessageErreur() << std::endl;

		std::cout << "---------------------------------------" << std::endl << std::endl;
	}

	std::cout << std::endl;
	std::cout << "-------- TESTS EXTRACTION AVEC POINT D'ORIGINE --------" << std::endl << std::endl;

	try
	{
		EXTExtraction.EXTExtractionPointOrigine(MATMatrice1, 1, 1, 2, 2).MATAfficher();
	}
	catch (CException EXCException)
	{
		std::cout << EXCException.EXCLireMessageErreur() << std::endl;

		std::cout << "---------------------------------------" << std::endl << std::endl;
	}

	std::cout << std::endl;
	std::cout << "-------- TESTS EXTRACTION AVEC POINT CENTRAL --------" << std::endl << std::endl;

	try
	{
		EXTExtraction.EXTExtractionPointCentrale(MATMatrice1, 2, 5, 2, 2).MATAfficher();
	}
	catch (CException EXCException)
	{
		std::cout << EXCException.EXCLireMessageErreur() << std::endl;

		std::cout << "---------------------------------------" << std::endl << std::endl;
	}

	std::cout << std::endl;
	std::cout << "-------- TESTS EXTRACTION DE TOUTE LES MATRICES POSSIBLE DE TAILLE DONNEE --------" << std::endl << std::endl;

	std::cout << "Nombre de matrice possible = " << (MATMatrice1.MATLireNbLigne() + 1 - uiTailleMatrice)*(MATMatrice1.MATLireNbColonne() + 1 - uiTailleMatrice) << std::endl << std::endl;

	try
	{
		pMATTableauMatrice = EXTExtraction.EXTExtractionCompleteMatriceCarree(MATMatrice1, uiTailleMatrice);
	}
	catch (CException EXCException)
	{
		std::cout << EXCException.EXCLireMessageErreur() << std::endl;

		std::cout << "---------------------------------------" << std::endl << std::endl;
	}

	try
	{
		for (size_t i = 0; i < (MATMatrice1.MATLireNbLigne() + 1 - uiTailleMatrice)*(MATMatrice1.MATLireNbColonne() + 1 - uiTailleMatrice); i++)
		{
			pMATTableauMatrice[i]->MATAfficher();
		}
	}
	catch (CException EXCException)
	{
		std::cout << EXCException.EXCLireMessageErreur() << std::endl;
	}

	std::cout << "---------------------------------------" << std::endl << std::endl;


}
