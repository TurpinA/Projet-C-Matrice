#include "CArc.h"


/***
**** Nom:			CArc
****
**** Description:	Constructeur par defaut
****
**** Precondition:
**** Entree:
**** Entraine:		Creation d'un objet CArc
**** Sortie:
***/
CArc::CArc()
{
	uiARCDestination = 0;
}

CArc::CArc(CArc & ARCParam)
{
	uiARCDestination = ARCParam.ARCLireDestination();
}

/***
**** Nom:			CArc
****
**** Description:	Constructeur de confort prenant la destination de l'arc en parametre
****
**** Precondition:
**** Entree:		unsigned int uiDestination
**** Entraine:		Creation d'un objet CArc
**** Sortie:
***/
CArc::CArc(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}

CArc::~CArc()
{
}

/***
**** Nom:			ARCModifierDestination
****
**** Description:	Cette methode modifie l'attribut uiARCDestination
****
**** Precondition:
**** Entree:		unsigned int uiDestination
**** Entraine:		Modification de la destination de l'objet
**** Sortie:
***/
void CArc::ARCModifierDestination(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}

/***
**** Nom:			ARCLireDestination
****
**** Description:	Cette methode renvoit la valeur de l'attribut uiARCDestination
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de la destination de l'arc
**** Sortie:		unsigned int
***/
unsigned int CArc::ARCLireDestination()
{
	return uiARCDestination;
}
