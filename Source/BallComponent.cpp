#include "Actor.h"

void BallComponent::postInit()
{
	EventManager::get()->addListener((IEventListener*)this, BALL_PADDLE_COLL);
	EventManager::get()->addListener((IEventListener*)this, BALL_BUMPER_COLL);
}

void BallComponent::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case BALL_PADDLE_COLL:
		onBallPaddleColl((BallPaddleCollEvtData*)e);
		break;
	case BALL_BUMPER_COLL:
		onBallBumperColl((BallBumperCollEvtData*)e);
		break;
	}

}

void BallComponent::onBallPaddleColl(BallPaddleCollEvtData *event)
{
	PaddleComponent *pc = (PaddleComponent*)event->getPaddle()->getComponent(PADDLE);
	PhysicalComponent *pPhys = (PhysicalComponent*)event->getPaddle()->getComponent(PHYSICAL);
	PhysicalComponent *bPhys = (PhysicalComponent*)parent->getComponent(PHYSICAL);

	bool collided = false;
	Vec2D<double> rebDir(0, 0);


	if (event->getRelDir() == R_UP_LEFT)
	{
		Vec2D<double> pTopLeft(
			pPhys->getPos().x - (((bm::Rect*)pPhys->getShape())->width / 2),
			pPhys->getPos().y - (((bm::Rect*)pPhys->getShape())->height / 2));
		rebDir = (bPhys->getPos() - pTopLeft);
		collided = true;
	}
	else if (event->getRelDir() == R_UP_RIGHT)
	{
		Vec2D<double> pTopRight(
			pPhys->getPos().x + (((bm::Rect*)pPhys->getShape())->width / 2),
			pPhys->getPos().y - (((bm::Rect*)pPhys->getShape())->height / 2));
		rebDir = (bPhys->getPos() - pTopRight);
		collided = true;
	}
	else if (event->getRelDir() == R_DOWN_LEFT)
	{
		Vec2D<double> pBottomLeft(
			pPhys->getPos().x - (((bm::Rect*)pPhys->getShape())->width / 2),
			pPhys->getPos().y + (((bm::Rect*)pPhys->getShape())->height / 2));
		rebDir = (bPhys->getPos() - pBottomLeft);
		collided = true;
	}
	else if (event->getRelDir() == R_DOWN_RIGHT)
	{
		Vec2D<double> pBottomRight(
			pPhys->getPos().x + (((bm::Rect*)pPhys->getShape())->width / 2),
			pPhys->getPos().y + (((bm::Rect*)pPhys->getShape())->height / 2));
		rebDir = (bPhys->getPos() - pBottomRight);
		collided = true;
	}

	if (collided)
	{
		Vec2D<double> ballVel = bPhys->getVelocity();
		Vec2D<double> paddleVel = pPhys->getVelocity();

		Vec2D<double> projBallVel = rebDir * ((ballVel.x * rebDir.x + ballVel.y * rebDir.y) / 
									(rebDir.x * rebDir.x + rebDir.y * rebDir.y));
		Vec2D<double> projPaddleVel = rebDir * ((paddleVel.x * rebDir.x + paddleVel.y * rebDir.y) / 
									  (rebDir.x * rebDir.x + rebDir.y * rebDir.y));

		Vec2D<double> velDifference = projPaddleVel - projBallVel;
		
		bPhys->addImpulse(projBallVel * -1);
		bPhys->addImpulse(projPaddleVel);
		bPhys->addImpulse(velDifference);
	}
	else if (pc->getOrientation() == HORIZONTAL)
	{
		if (event->getRelDir() == R_UP || event->getRelDir() == R_DOWN)
		{
			bPhys->addImpulse(Vec2D<double>(0, bPhys->getVelocity().y * -2));		
			// clear the curve applied from previous hits
			bPhys->clearForces(); 
			// apply spin
			bPhys->addForce(Vec2D<double>(pPhys->getVelocity().x * -.3, 0)); 
		}
		else if (event->getRelDir() == R_LEFT || event->getRelDir() == R_RIGHT)
		{
			// clear spin
			bPhys->clearForces(); 
			
			double xVel = pPhys->getVelocity().x - bPhys->getVelocity().x;
			// clear x-velocity and then update it
			bPhys->addImpulse(Vec2D<double>(bPhys->getVelocity().x * -1, 0));
			bPhys->addImpulse(Vec2D<double>(pPhys->getVelocity().x, 0));
			bPhys->addImpulse(Vec2D<double>(xVel, 0));
		}
	}
	else // orientation = VERTICAL
	{
		if (event->getRelDir() == R_LEFT || event->getRelDir() == R_RIGHT)
		{
			bPhys->addImpulse(Vec2D<double>(bPhys->getVelocity().x * -2, 0));		
			// clear the curve applied from previous hits
			bPhys->clearForces(); 
			// apply spin
			bPhys->addForce(Vec2D<double>(0, pPhys->getVelocity().y * -.3)); 
		}
		else if (event->getRelDir() == R_UP || event->getRelDir() == R_DOWN)
		{
			// clear spin
			bPhys->clearForces(); 

			double yVel = pPhys->getVelocity().y - bPhys->getVelocity().y;
			// clear y-velocity and then update it
			bPhys->addImpulse(Vec2D<double>(0, bPhys->getVelocity().y * -1));
			bPhys->addImpulse(Vec2D<double>(0, pPhys->getVelocity().y));
			bPhys->addImpulse(Vec2D<double>(0, yVel));
		}
	}
}

void BallComponent::onBallBumperColl(BallBumperCollEvtData *event)
{
	PhysicalComponent *bumpPhys = (PhysicalComponent*)event->getBumper()->getComponent(PHYSICAL);
	PhysicalComponent *ballPhys = (PhysicalComponent*)parent->getComponent(PHYSICAL);

	Vec2D<double> rebDir = ballPhys->getPos() - bumpPhys->getPos();
	Vec2D<double> ballVel = ballPhys->getVelocity();

	Vec2D<double> projBallVel = rebDir * ((ballVel.x * rebDir.x + ballVel.y * rebDir.y) / 
								(rebDir.x * rebDir.x + rebDir.y * rebDir.y));

	ballPhys->addImpulse(projBallVel * -2);
}

