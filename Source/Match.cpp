#include "Pong.h"

void Match::init() 
{
	volley = new Volley(humanView);
}

void Match::update(double totalTime, double elapsedTime)
{
	volley->update(totalTime, elapsedTime);
}

