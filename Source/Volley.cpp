#include "Pong.h"

void Volley::init()
{
	isReset = true;
	EventManager::get()->addListener((IEventListener*)this, LAUNCH_BALL);
	EventManager::get()->addListener((IEventListener*)this, SCORE);
	field = ActorFactory::get()->createActor("Field.xml");

	createPlayer(1, p1Horiz, p1Vert);
	createPlayer(2, p2Horiz, p2Vert);
	paddles.push_back(p1Horiz);
	paddles.push_back(p2Horiz);
	paddles.push_back(p1Vert);
	paddles.push_back(p2Vert);

	makeBumpers();
	makeBall();
}

void Volley::reset()
{
	//resetPlayerPos(1, p1Horiz, p1Vert);
	//resetPlayerPos(2, p2Horiz, p2Vert);
	resetBall();
	isReset = true;
}


void Volley::update(double totalTime, double elapsedTime)
{
	// Go through the paddles
	for (auto i = paddles.begin(); i != paddles.end(); i++)
	{
		// update and draw the paddle
		// sensitive: this must go before the paddle collisions
		(*i)->update(totalTime, elapsedTime);
		humanView->drawActor(*i);
		
		// If the paddle collides with a bumper, fire a collision event
		for (auto j = bumpers.begin(); j != bumpers.end(); j++)
		{
			PhysicalComponent *bPhys = (PhysicalComponent*)(*j)->getComponent(PHYSICAL);
			PhysicalComponent *pPhys = (PhysicalComponent*)(*i)->getComponent(PHYSICAL);

			if (Collision::collide(bPhys, pPhys))
			{
				BumperPaddleCollEvtData *e = new BumperPaddleCollEvtData((*j)->getId(), (*i)->getId());
				EventManager::get()->queueEvent((IEventData*)e);
			}
		}
	}
	// update and draw the bumpers
	for (auto i = bumpers.begin(); i != bumpers.end(); i++)
	{
		(*i)->update(totalTime, elapsedTime);
		humanView->drawActor(*i);
	}

	// update and draw the ball
	ball->update(totalTime, elapsedTime);
	humanView->drawActor(ball);

	PhysicalComponent *bPhys = (PhysicalComponent*)ball->getComponent(PHYSICAL);
	for (auto i = paddles.begin(); i != paddles.end(); i++)
	{
		PhysicalComponent *pPhys = (PhysicalComponent*)(*i)->getComponent(PHYSICAL);
		if (Collision::collide(pPhys, bPhys))
		{
			RelativeDir relDir = getRelDir(ball, *i);
			BallPaddleCollEvtData *e = new BallPaddleCollEvtData(*i, relDir);
			EventManager::get()->queueEvent((IEventData*)e);
		}
	}
	for (auto i = bumpers.begin(); i != bumpers.end(); i++)
	{
		PhysicalComponent *bumpPhys = (PhysicalComponent*)(*i)->getComponent(PHYSICAL);
		if (Collision::collide(bPhys, bumpPhys))
		{
			BallBumperCollEvtData *e = new BallBumperCollEvtData(*i);
			EventManager::get()->queueEvent((IEventData*)e);
		}
	}
	PhysicalComponent *fieldPhys = (PhysicalComponent*)field->getComponent(PHYSICAL);
	// if the ball doesn't collide with the field
	if (!Collision::collide(bPhys, fieldPhys))
	{
		int scorer;
		switch (getRelDir(ball, field))
		{
		case R_LEFT:
		case R_UP:
			scorer = 2;
			break;
		case R_RIGHT:
		case R_DOWN:
			scorer = 1;
			break;
		default:
			throw SCORE_ERR;
		}
		ScoreEvtData *e = new ScoreEvtData(scorer);
		EventManager::get()->queueEvent((IEventData*)e);
	}
}

void Volley::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case SCORE:
		onScore((ScoreEvtData*)e);
		break;
	case LAUNCH_BALL:
		onLaunchBall((LaunchBallEvtData*)e);
		break;
	}
}

void Volley::onScore(ScoreEvtData *event)
{
	reset();
}

void Volley::onLaunchBall(LaunchBallEvtData *event)
{
	if (isReset)
	{
		Vec2D<double> direction(rand() % 300 - 150, rand() % 300 - 150);
		direction = direction.normalize();
		((PhysicalComponent*)ball->getComponent(PHYSICAL))->addImpulse(direction * 100);
	}
	isReset = false;
}


void Volley::resetPlayerPos(int player, Actor * &horiz, Actor * &vert)
{
	if (player == 1)
	{
		// set the position and color for player 1
		((PhysicalComponent*)horiz->getComponent(PHYSICAL))->setPos(400, 25);
		((PhysicalComponent*)vert->getComponent(PHYSICAL))->setPos(25, 300);
	}
	else if (player == 2)
	{
		// set the position and color for player 2
		((PhysicalComponent*)horiz->getComponent(PHYSICAL))->setPos(400, 575);
		((PhysicalComponent*)vert->getComponent(PHYSICAL))->setPos(775, 300);
	}
}

void Volley::createPlayer(int player, Actor	* &horiz, Actor * &vert)
{
	horiz = ActorFactory::get()->createActor("HorizontalPaddle.xml");
	vert = ActorFactory::get()->createActor("VerticalPaddle.xml");

	((PaddleComponent*)horiz->getComponent(PADDLE))->setPlayer(player);
	((PaddleComponent*)vert->getComponent(PADDLE))->setPlayer(player);

	resetPlayerPos(player, horiz, vert);
	if (player == 1)
	{
		((VisualComponent*)horiz->getComponent(VISUAL))->setColor(100, 255, 120, 255);
		((VisualComponent*)vert->getComponent(VISUAL))->setColor(100, 255, 120, 255);
	}
	else if (player == 2)
	{
		((VisualComponent*)horiz->getComponent(VISUAL))->setColor(100, 200, 255, 255);
		((VisualComponent*)vert->getComponent(VISUAL))->setColor(100, 200, 255, 255);
	}
}

void Volley::makeBumpers()
{
	ActorFactory af;
	bumperBL = ActorFactory::get()->createActor("Bumper.xml");
	bumperBR = ActorFactory::get()->createActor("Bumper.xml");
	bumperTL = ActorFactory::get()->createActor("Bumper.xml");
	bumperTR = ActorFactory::get()->createActor("Bumper.xml");

	PhysicalComponent *physBL = (PhysicalComponent*)bumperBL->getComponent(PHYSICAL);
	PhysicalComponent *physBR = (PhysicalComponent*)bumperBR->getComponent(PHYSICAL);
	PhysicalComponent *physTL = (PhysicalComponent*)bumperTL->getComponent(PHYSICAL);
	PhysicalComponent *physTR = (PhysicalComponent*)bumperTR->getComponent(PHYSICAL);

	physBL->setPos(0, 600);
	physBR->setPos(800, 600);
	physTL->setPos(0, 0);
	physTR->setPos(800, 0);

	bumpers.push_back(bumperBL);
	bumpers.push_back(bumperBR);
	bumpers.push_back(bumperTL);
	bumpers.push_back(bumperTR);
}

void Volley::resetBall()
{
	PhysicalComponent *phys = (PhysicalComponent*)ball->getComponent(PHYSICAL);
	phys->setPos(400, 300);
	phys->clearVelocity();
	phys->clearForces();
}

void Volley::makeBall()
{
	ball = ActorFactory::get()->createActor("Ball.xml");
	PhysicalComponent *phys = (PhysicalComponent*)ball->getComponent(PHYSICAL);
}

RelativeDir Volley::getRelDir(Actor *ball, Actor *paddle)
{
	PhysicalComponent *bPhys = (PhysicalComponent*)ball->getComponent(PHYSICAL);
	Vec2D<double> bPos = bPhys->getPos();
	PhysicalComponent *pPhys = (PhysicalComponent*)paddle->getComponent(PHYSICAL);
	Vec2D<double> pPos = pPhys->getPos();
	double pWidth = ((bm::Rect*)pPhys->getShape())->width;
	double pHeight = ((bm::Rect*)pPhys->getShape())->height;

	// if the ball's y-component is within bounds of the height of the paddle
	if (abs(bPos.y - pPos.y) <= pHeight / 2)
	{
		// if the ball is to the left of the paddle, return left. Otherwise, return right
		if (bPos.x < pPos.x)
			return R_LEFT;
		else
			return R_RIGHT;
	}
	// if the ball's x-component is within bounds of the width of the paddle
	else if (abs(bPos.x - pPos.x) <= pWidth / 2)
	{
		// if the ball is above the paddle, return up. Otherwise, return down.
		if (bPos.y < pPos.y)
			return R_UP;
		else
			return R_DOWN;
	}
	else if (bPos.x < pPos.x)
	{
		if (bPos.y < pPos.y)
			return R_UP_LEFT;
		else
			return R_DOWN_LEFT;
	}
	else
	{
		if (bPos.y < pPos.y)
			return R_UP_RIGHT;
		else
			return R_DOWN_RIGHT;
	}
}