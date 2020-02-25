#include "CGraphe.h"
#include "CParser.h"

int main(int argc, char *argv[])
{
	try
	{
		if (argc > 1)
		{
			std::cout << "---------------------------------------" << std::endl << std::endl;

			std::cout << "     GRAPHE PASSE EN PARAMETRE     " << std::endl << std::endl;
			try
			{
				CGraphe GRAGrapheTest(argv[1]);
				GRAGrapheTest.GRAAfficherGraphe();

				std::cout << std::endl;

				std::cout << "     GRAPHE PASSE EN PARAMETRE INVERSE     " << std::endl << std::endl;


				(GRAGrapheTest.GRAInverserGraphe()).GRAAfficherGraphe();
			}
			catch (CException e)
			{
				std::cout << e.EXCLireMessageErreur() << std::endl << std::endl;
			}
		}

		std::cout << std::endl;

		std::cout << "-------- TESTS SUPPLEMENTAIRES --------" << std::endl << std::endl;

		CGraphe GRAGraphe;
		GRAGraphe.GRAAjouterSommet(1);
		GRAGraphe.GRAAjouterSommet(2);
		GRAGraphe.GRAAjouterSommet(3);
		GRAGraphe.GRAAjouterSommet(4);
		GRAGraphe.GRARelierSommets(1, 2);
		GRAGraphe.GRARelierSommets(2, 3);
		GRAGraphe.GRARelierSommets(3, 1);
		GRAGraphe.GRARelierSommets(4, 1);
		GRAGraphe.GRARelierSommets(3, 4);
		GRAGraphe.GRARelierSommets(2, 4);
		
		std::cout << "     GRAPHE DE TEST     " << std::endl << std::endl;

		GRAGraphe.GRAAfficherGraphe();

		std::cout << std::endl;
		
		GRAGraphe.GRARelierSommets(3, 2);

		std::cout << "     On relie les point 3 -> 2     " << std::endl << std::endl;

		GRAGraphe.GRAAfficherGraphe();

		std::cout << std::endl;

		GRAGraphe.GRASupprimerSommet(2);

		std::cout << "     On supprime le sommet 2     " << std::endl << std::endl;

		GRAGraphe.GRAAfficherGraphe();

		std::cout << std::endl;

		std::cout << "     On inverse le graphe     " << std::endl << std::endl;

		(GRAGraphe.GRAInverserGraphe()).GRAAfficherGraphe();

		GRAGraphe.GRASupprimerGraphe();

		std::cout << std::endl;

		std::cout << "     On supprime le graphe     " << std::endl << std::endl;

		GRAGraphe.GRAAfficherGraphe();


	}
	catch (CException e)
	{
		std::cout << e.EXCLireMessageErreur() << std::endl << std::endl;
	}

	std::cout << "---------------------------------------" << std::endl << std::endl;
	
	return 0;
}