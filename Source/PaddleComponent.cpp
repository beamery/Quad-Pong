#include "Actor.h"

void PaddleComponent::init(XMLElement *xmlData)
{
	player = xmlData->IntAttribute("player");
	// If no player is supplied, throw an error
	if (player == 0)
		throw INVALID_PLAYER_ERR;
	
	string orientStr = xmlData->Attribute("orientation");
	if (orientStr.compare("horizontal") == 0)
		orientation = HORIZONTAL;
	else if (orientStr.compare("vertical") == 0)
		orientation = VERTICAL;
	else
		throw INVALID_ORIENTATION_ERR;

}

void PaddleComponent::postInit()
{
	EventManager::get()->addListener((IEventListener*)this, PADDLE_MOVE);
	EventManager::get()->addListener((IEventListener*)this, BUMPER_PADDLE_COLL);
	paddleForce = 3000;
	forceOfFriction = 2000;
}

void PaddleComponent::update(double totalTime, double elapsedTime)
{
	// Apply friction to the paddle
	PhysicalComponent *phys = (PhysicalComponent*)parent->getComponent(PHYSICAL);
	Vec2D<double> vel = phys->getVelocity();
	if (vel.length() != 0)
	{
		vel = vel.normalize();
		vel = vel * -1 * forceOfFriction * elapsedTime;
		phys->addImpulse(vel);
	}
}

void PaddleComponent::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case PADDLE_MOVE:
		onPaddleMove((PaddleMoveEvtData*)e); break;
	case BUMPER_PADDLE_COLL:
		onBumperPaddleColl((BumperPaddleCollEvtData*)e); break;
	}
}


void PaddleComponent::onPaddleMove(PaddleMoveEvtData *event)
{
	// If this is not the paddle being moved, do nothing
	if (event->getPlayer() != player)
		return;

	PhysicalComponent *phys = (PhysicalComponent*)parent->getComponent(PHYSICAL);
	if (orientation == HORIZONTAL)
	{
		switch (event->getDirection())
		{
		case LEFT:
			if (event->isStarting())
			{
				phys->addForce(Vec2D<double>(-paddleForce, 0));
			}
			else
				phys->removeForce(Vec2D<double>(-paddleForce, 0));
			break;
		case RIGHT:
			if (event->isStarting())
			{
				phys->addForce(Vec2D<double>(paddleForce, 0));
			}
			else
				phys->removeForce(Vec2D<double>(paddleForce, 0));
			break;
		default:
			break;
		}
	}
	else 
	{
		switch (event->getDirection())
		{
		case UP:
			if (event->isStarting())
			{
				phys->addForce(Vec2D<double>(0, -paddleForce));
			}
			else
				phys->removeForce(Vec2D<double>(0, -paddleForce));
			break;
		case DOWN:
			if (event->isStarting())
			{
				phys->addForce(Vec2D<double>(0, paddleForce));
			}
			else
				phys->removeForce(Vec2D<double>(0, paddleForce));
			break;
		default:
			break;
		}
	}
}

void PaddleComponent::onBumperPaddleColl(BumperPaddleCollEvtData *event)
{
	if (event->getPaddle() == parent->getId())
	{
		PhysicalComponent *phys = (PhysicalComponent*)parent->getComponent(PHYSICAL);
		phys->addImpulse(phys->getVelocity() * -2.01);
	}
}
