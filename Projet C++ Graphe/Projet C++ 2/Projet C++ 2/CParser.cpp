#include "CParser.h"

#define ErreurFichier 10

/***
**** Nom:			CParser
****
**** Description:	Constructeur de confort
****
**** Precondition:
**** Entree:		const char * pcChemin
**** Entraine:		Creation de l'objet parser et ouverture du fichier passe en parametre
**** Sortie:		
***/
CParser::CParser(const char * pcChemin)
{
	fichier.open(pcChemin, std::ifstream::in);
	if (!fichier)
	{
		throw  CException(ErreurFichier, "ERREUR DANS L'OUVERTURE DU FICHIER");
	}

	saveCursor = fichier.beg;
}

/***
**** Nom:			~CParser
****
**** Description:	Destructeur de la classe
****
**** Precondition:
**** Entree:		
**** Entraine:		Destruction de l'objet avec la fermeture du fichier dans un premier temps
**** Sortie:
***/
CParser::~CParser()
{
	fichier.close();
}

/***
**** Nom:			PARGetAttribut
****
**** Description:	Cette methode revoit le chaine de caractere se trouvant a gauche du egale
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de l'attribut de la ligne
**** Sortie:		char *
***/
char * CParser::PARGetAttribut()
{
	char *cLigne = (char*)malloc(sizeof(char)*256);
	fichier.getline(cLigne, 256, '=');
	return cLigne;
}

/***
**** Nom:			PARGetValeurLine
****
**** Description:	Cette methode revoit le chaine de caractere se trouvant a droite du egale
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit de le reste de la ligne apres le egale
**** Sortie:		char *
***/
char * CParser::PARGetValeurLine()
{
	char *cLigne = (char*)malloc(sizeof(char) * 256);
	fichier.getline(cLigne, 256);
	return cLigne;
}

/***
**** Nom:			PARGetValeur
****
**** Description:	Cette methode revoit le mot se trouvant a droite du egale
****
**** Precondition:
**** Entree:
**** Entraine:		Renvoit le mot se trouvant apres le egale
**** Sortie:		char *
***/
char * CParser::PARGetValeur()
{
	char *cLigne = (char*)malloc(sizeof(char) * 256);
	fichier >> cLigne;
	return cLigne;
}

/***
**** Nom:			PARGetValeurJusque
****
**** Description:	Cette methode revoit le chaine de caractere se trouvant a droite du egale et s'arretant au caractere place en parametre
****
**** Precondition:
**** Entree:
**** Entraine:		Revoit le chaine de caractere se trouvant a droite du egale et s'arretant au caractere place en parametre
**** Sortie:		char *
***/
char * CParser::PARGetValeurJusque(char cStop)
{
	char *cLigne = (char*)malloc(sizeof(char) * 256);
	fichier.getline(cLigne, 256, cStop);
	return cLigne;
}

/***
**** Nom:			PARSaveCursorInFile
****
**** Description:	Cette methode sauvegarde le curseur du fichier a position actuelle
****
**** Precondition:
**** Entree:
**** Entraine:		saveCursor contient la position actuelle du curseur dans le fichier
**** Sortie:		
***/
void CParser::PARSaveCursorInFile()
{
	saveCursor = fichier.tellg();
}

/***
**** Nom:			PARPlaceCursorToSave
****
**** Description:	Cette methode replace le curseur du fichier a position sauvegarde plus tot a l'attribut saveCursor
****
**** Precondition:
**** Entree:
**** Entraine:		Place le curseur du fichier a saveCursor
**** Sortie:		
***/
void CParser::PARPlaceCursorToSave()
{
	fichier.seekg(saveCursor, fichier.beg);
}
