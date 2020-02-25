#ifndef CArc_h
#define CArc_h

#include "CException.h"

class CArc
{
	private :

		unsigned int uiARCDestination;

	public:

		CArc();
		CArc(CArc& ARCParam);
		CArc(unsigned int uiDestination);
		~CArc();

		void ARCModifierDestination(unsigned int uiDestination);
		unsigned int ARCLireDestination();

};

#endif

