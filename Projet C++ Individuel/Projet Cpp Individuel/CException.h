#include <stdlib.h>
#include <stdio.h>

#ifndef CException_h
#define CException_h

class CException
{
private:
	unsigned int uiEXCErreur;
	char* pcEXCMessage;

public:
	CException(unsigned int uiErreur, const char* pcMessage);
	~CException();

public:
	unsigned int EXCLireErreur();
	void EXCModifierErreur(unsigned int uiErreur);
	char* EXCLireMessageErreur();
	void EXCModifierMessageErreur(const char* pcMessage);
};

#endif
