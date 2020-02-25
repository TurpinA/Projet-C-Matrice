#ifndef CParser_h
#define CParser_h

#include <iostream>
#include <fstream>
#include "CException.h"

class CParser
{
	std::ifstream fichier;
	std::streamoff saveCursor;

public:

	CParser(const char* pcChemin);
	~CParser();

	char* PARGetAttribut();
	char* PARGetValeurLine();
	char* PARGetValeur();
	char* PARGetValeurJusque(char cStop);
	void PARSaveCursorInFile();
	void PARPlaceCursorToSave();
};

#endif

