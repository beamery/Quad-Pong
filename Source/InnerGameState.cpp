#include "GameState.h"
#include "Event.h"
#include "Actor.h"
#include "Collision.h"

void InnerGameState::init()
{
	
	timer = 0;
	ActorFactory af;
	createPlayer(1, p1Horiz, p1Vert);
	createPlayer(2, p2Horiz, p2Vert);
	paddles.push_back(p1Horiz);
	paddles.push_back(p2Horiz);
	paddles.push_back(p1Vert);
	paddles.push_back(p2Vert);
	makeBumpers();

	humanView = new HumanView();
	bindKeys();
}

void InnerGameState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

	timer += elapsedTime;

	for (auto i = paddles.begin(); i != paddles.end(); i++)
	{
		(*i)->update(totalTime, elapsedTime);
		humanView->drawActor(*i);

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
	for (auto i = bumpers.begin(); i != bumpers.end(); i++)
	{
		(*i)->update(totalTime, elapsedTime);
		humanView->drawActor(*i);
	}

	/*if (timer > 10)
	{

		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("game_over", "inner_game", true);

		EventManager::get()->queueEvent((IEventData*)data);
	}*/

}

void InnerGameState::bindKeys()
{
	PaddleMoveEvtData *moveUpP1 = new PaddleMoveEvtData(1, UP);
	PaddleMoveEvtData *moveRightP1 = new PaddleMoveEvtData(1, RIGHT);
	PaddleMoveEvtData *moveLeftP1 = new PaddleMoveEvtData(1, LEFT);
	PaddleMoveEvtData *moveDownP1 = new PaddleMoveEvtData(1, DOWN);

	humanView->keyboardHandler->bind(sf::Keyboard::W, (IEventData*)moveUpP1);
	humanView->keyboardHandler->bind(sf::Keyboard::A, (IEventData*)moveLeftP1);
	humanView->keyboardHandler->bind(sf::Keyboard::S, (IEventData*)moveDownP1);
	humanView->keyboardHandler->bind(sf::Keyboard::D, (IEventData*)moveRightP1);

	PaddleMoveEvtData *moveUpP2 = new PaddleMoveEvtData(2, UP);
	PaddleMoveEvtData *moveRightP2 = new PaddleMoveEvtData(2, RIGHT);
	PaddleMoveEvtData *moveLeftP2 = new PaddleMoveEvtData(2, LEFT);
	PaddleMoveEvtData *moveDownP2 = new PaddleMoveEvtData(2, DOWN);

	humanView->keyboardHandler->bind(sf::Keyboard::Up, (IEventData*)moveUpP2);
	humanView->keyboardHandler->bind(sf::Keyboard::Left, (IEventData*)moveLeftP2);
	humanView->keyboardHandler->bind(sf::Keyboard::Down, (IEventData*)moveDownP2);
	humanView->keyboardHandler->bind(sf::Keyboard::Right, (IEventData*)moveRightP2);
}

void InnerGameState::createPlayer(int player, Actor	* &horiz, Actor * &vert)
{
	ActorFactory af;
	horiz = af.createActor("HorizontalPaddle.xml");
	vert = af.createActor("VerticalPaddle.xml");

	((PaddleComponent*)horiz->getComponent(PADDLE))->setPlayer(player);
	((PaddleComponent*)vert->getComponent(PADDLE))->setPlayer(player);

	if (player == 1)
	{
		((PhysicalComponent*)horiz->getComponent(PHYSICAL))->setPos(400, 25);
		((PhysicalComponent*)vert->getComponent(PHYSICAL))->setPos(25, 300);

		((VisualComponent*)horiz->getComponent(VISUAL))->setColor(100, 255, 120, 255);
		((VisualComponent*)vert->getComponent(VISUAL))->setColor(100, 255, 120, 255);

	}
	else if (player == 2)
	{
		((PhysicalComponent*)horiz->getComponent(PHYSICAL))->setPos(400, 575);
		((PhysicalComponent*)vert->getComponent(PHYSICAL))->setPos(775, 300);

		((VisualComponent*)horiz->getComponent(VISUAL))->setColor(100, 200, 255, 255);
		((VisualComponent*)vert->getComponent(VISUAL))->setColor(100, 200, 255, 255);
	}
}

void InnerGameState::makeBumpers()
{
	ActorFactory af;
	bumperBL = af.createActor("Bumper.xml");
	bumperBR = af.createActor("Bumper.xml");
	bumperTL = af.createActor("Bumper.xml");
	bumperTR = af.createActor("Bumper.xml");

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
