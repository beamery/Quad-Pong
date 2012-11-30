#ifndef ERROR_H
#define ERROR_H

enum Status
{
// no error

	OK = 0, NOTUSED = -999,

// Game state errors
	STATE_INIT_ERR, UPDATE_ERR, INVALID_STATE_ERROR

};

class Error
{
public:
	void print(Status status);
};

#endif