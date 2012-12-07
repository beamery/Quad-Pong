#include "Error.h"
#include <iostream>

using namespace std;

void Error::print(Status status)
{
	cerr << "Error: ";
	switch (status)
	{

	// no error
	case OK:	
		cerr << "no error"; break;
	case INVALID_STATE_ERR: 
		cerr << "invalid state"; break;
	case DUPLICATE_LISTENER_ERR:
		cerr << "duplicate listener"; break;
	case NO_SUCH_COMPONENT_ERR:
		cerr << "no such component exists"; break;
	case DUPLICATE_COMPONENT_ERR:
		cerr << "actor already has that component"; break;

	default:	
		cerr << "undefined error code: " << status;

	}
	cerr << endl;
}