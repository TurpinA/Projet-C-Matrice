#include "CException.h"

/***
**** Nom:			CException
****
**** Description:	Constructeur de confort. Ce constructeur cr�er l'exception avec l'id et le message pass� en param�tre.
****
**** Precondition:
**** Entree:		unsigned int uiErreur, const char* pcMessage
**** Entraine:		L'objet Exception est cr�er avec les param�tres donn�es
**** Sortie:
***/
CException::CException(unsigned int uiErreur, const char* pcMessage)
{
	uiEXCErreur = uiErreur;

	pcEXCMessage = new char[256];

	char* pSave = pcEXCMessage;

	while (*pcMessage != '\0')
	{
		*pcEXCMessage = *pcMessage;
		pcEXCMessage++;
		pcMessage++;
	}

	*pcEXCMessage = '\0';

	pcEXCMessage = pSave;
}


/***
**** Nom:			~CException
****
**** Description:	C'est le destructeur de la classe. Il permet de d�truire l'objet.
****
**** Precondition:
**** Entree:
**** Entraine:
**** Sortie:
***/
CException::~CException()
{
}


/***
**** Nom:			EXCLireErreur
****
**** Description:	Cette m�thode est un accesseur en lecture sur l'id d'erreur de l'exception.
****
**** Precondition:
**** Entree:
**** Entraine:	    Retourne l'id de l'exception.
**** Sortie:        usigned int uiEXCErreur
***/
unsigned int CException::EXCLireErreur()
{
	return uiEXCErreur;
}

/***
**** Nom:			EXCModifierErreur
****
**** Description:	Cette m�thode est un accesseur en �criture sur l'id d'erreur de l'exception.
****
**** Precondition:
**** Entree:		unsigned int uiErreur
**** Entraine:	    Modifie l'id d'erreur de l'exception.
**** Sortie:
***/
void CException::EXCModifierErreur(unsigned int uiErreur)
{
	uiEXCErreur = uiErreur;
}

/***
**** Nom:			EXCLireMessageErreur
****
**** Description:	Cette m�thode est un accesseur en lecture sur le message d'erreur de l'exception.
****
**** Precondition:
**** Entree:
**** Entraine:	    Retourne le message d'erreur de l'exception.
**** Sortie:        char* pcEXCMessage
***/
char* CException::EXCLireMessageErreur()
{
	return pcEXCMessage;
}

/***
**** Nom:			EXCModifierMessageErreur
****
**** Description:	Cette m�thode est un accesseur en �criture sur le message d'erreur de l'exception.
****
**** Precondition:
**** Entree:		char* pcMessage
**** Entraine:	    Modifie le message d'erreur de l'exception.
**** Sortie:
***/
void CException::EXCModifierMessageErreur(const char* pcMessage)
{
	pcEXCMessage = new char[256];

	char* pSave = pcEXCMessage;

	while (*pcMessage != '\0')
	{
		*pcEXCMessage = *pcMessage;
		pcEXCMessage++;
		pcMessage++;
	}

	*pcEXCMessage = '\0';

	pcEXCMessage = pSave;
}
