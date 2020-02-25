#ifndef CGraphe_h
#define CGraphe_h

#include "CArc.h"
#include "CException.h"
#include "CSommet.h"
#include "config.h"
#include "CParser.h"

class CGraphe
{
	private:
		unsigned int uiGRANbSommet;
		unsigned int uiGRANbArc;
		unsigned int uiGRATailleAlloueListe;

		CSommet** pSOMGRAListeSommet;

	public:
		CGraphe();
		CGraphe(CGraphe& GRAGraphe);
		CGraphe(CGraphe&& GRAGraphe);
		CGraphe(const char * pcChemin);
		~CGraphe();

		void GRAAfficherGraphe();
		void GRAAjouterSommet(unsigned int uiNumero = 0);
		void GRARelierSommets(unsigned int uiSommetDepart, unsigned int uiSommetArriver);
		void GRADelierSommets(unsigned int uiSommetDepart, unsigned int uiSommetArriver);
		void GRASupprimerGraphe();
		void GRASupprimerSommet(unsigned int uiSommet);

		unsigned int GRALireNbSommet();
		unsigned int GRALireNbArc();
		unsigned int GRALireTailleAlloueListe();
		CSommet* GRALireListeSommet(unsigned int uiPosition);
		CSommet* GRATrouverSommet(unsigned int uiSommet);

		CGraphe GRAInverserGraphe();
		CGraphe& operator=(CGraphe& GRAGraphe);
};
#endif
