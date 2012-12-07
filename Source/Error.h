#ifndef ERROR_H
#define ERROR_H

enum Status
{
// no error

	OK = 0, NOTUSED = -999,

// Game state errors
	STATE_INIT_ERR, UPDATE_ERR, INVALID_STATE_ERR, 

// Game event errors
	DUPLICATE_LISTENER_ERR,

// Actor errors
	NO_SUCH_COMPONENT_ERR, DUPLICATE_COMPONENT_ERR,

};

class Error
{
public:
	void print(Status status);
};

#endif