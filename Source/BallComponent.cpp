#include "Actor.h"

void BallComponent::init(XMLElement *xmlData)
{

}

void BallComponent::postInit()
{

}


void BallComponent::update(double totalTime, double elapsedTime)
{

}

void BallComponent::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case BALL_PADDLE_COLL:
		onBallPaddleColl((BallPaddleCollEvtData*)e);
	}

}

void BallComponent::onBallPaddleColl(BallPaddleCollEvtData *event)
{

}
