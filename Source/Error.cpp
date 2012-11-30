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
	case INVALID_STATE_ERROR: 
		cerr << "invalid state"; break;

	default:	
		cerr << "undefined error code: " << status;

	}
	cerr << endl;
}