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

	humanView = new HumanView();
	bindKeys();
}

void InnerGameState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

	timer += elapsedTime;

	p1Vert->update(totalTime, elapsedTime);
	p2Vert->update(totalTime, elapsedTime);
	p1Horiz->update(totalTime, elapsedTime);
	p2Horiz->update(totalTime, elapsedTime);
	humanView->drawActor(p1Vert);
	humanView->drawActor(p2Vert);
	humanView->drawActor(p1Horiz);
	humanView->drawActor(p2Horiz);

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
		((PhysicalComponent*)horiz->getComponent(PHYSICAL))->setPos(400, 30);
		((PhysicalComponent*)vert->getComponent(PHYSICAL))->setPos(30, 300);

		((VisualComponent*)horiz->getComponent(VISUAL))->setColor(30, 200, 30, 220);
		((VisualComponent*)vert->getComponent(VISUAL))->setColor(30, 200, 30, 220);

	}
	else if (player == 2)
	{
		((PhysicalComponent*)horiz->getComponent(PHYSICAL))->setPos(400, 570);
		((PhysicalComponent*)vert->getComponent(PHYSICAL))->setPos(770, 300);

		((VisualComponent*)horiz->getComponent(VISUAL))->setColor(30, 150, 200, 220);
		((VisualComponent*)vert->getComponent(VISUAL))->setColor(30, 150, 200, 220);
	}
}
