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
	case OBJ_NOT_MOVABLE:
		cerr << "tried to move an immovable object"; break;
	case BAD_SHAPE_ERR:
		cerr << "invalid shape"; break;
	case MULTIPLE_SHAPE_ERR:
		cerr << "component assigned more than one shape"; break;
	case NULL_SHAPE_ERR:
		cerr << "component was not assigned a shape"; break;
	case INVALID_TEXTURE_ERR:
		cerr << "that texture does not exist"; break;
	case INVALID_TEXTURE_PATH:
		cerr << "there is no texture at that path"; break;
	case BAD_DIMENSION_ERR:
		cerr << "no texture and no dimension given"; break;

	default:	
		cerr << "undefined error code: " << status;

	}
	cerr << endl;
}