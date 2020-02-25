#ifndef CSommet_h
#define CSommet_h

#include "CArc.h"
#include "config.h"
#include "CException.h"

class CSommet
{
	private:

		unsigned int uiSOMNumero;
		unsigned int uiSOMNbArrivant;
		unsigned int uiSOMNbPartant;
		CArc** pARCSOMArrivant;
		CArc** pARCSOMPartant;

	public:

		CSommet(unsigned int uiNumero);
		CSommet(CSommet& SOMSommet);
		~CSommet();

		void SOMAjouterArrivant(unsigned int uiNumero);
		void SOMAjouterPartant(unsigned int uiNumero);
		void SOMSupprimerArrivant(unsigned int uiNumero);
		void SOMSupprimerPartant(unsigned int uiNumero);
		void SOMModifierNumero(unsigned int uiNumero);
		void SOMModifierArrivant(unsigned int uiOldNumero, unsigned int uiNewNumero);
		void SOMModifierPartant(unsigned int uiOldNumero, unsigned int uiNewNumero);
		bool SOMArcPartantPresent(unsigned int uiNumero);
		bool SOMArcArrivantPresent(unsigned int uiNumero);
		unsigned int SOMLireNumero();
		unsigned int SOMLireNbArrivant();
		unsigned int SOMLireNbPartant();
		void SOMModifierNbArrivant(unsigned int uiNbArrivant);
		void SOMModifierNbPartant(unsigned int uiNbPartant);
		CArc** SOMLireListeArrivant();
		CArc ** SOMLireListePartant();
		void SOMModifierListeArrivant(CArc ** pARCParam);
		void SOMModifierListePartant(CArc ** pARCParam);
		CArc* SOMLireArrivant(unsigned int uiPosition);
		CArc* SOMLirePartant(unsigned int uiPosition);
		CSommet& operator=(CSommet& SOMSommet);
};
#endif

