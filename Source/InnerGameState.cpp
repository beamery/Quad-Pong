#include "GameState.h"
#include "Event.h"
#include "Actor.h"
#include "Collision.h"

void InnerGameState::init()
{
	timer = 0;
	humanView = new HumanView();
	bindKeys();
	
	match = new Match(humanView);
}

void InnerGameState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	timer += elapsedTime;

	match->update(totalTime, elapsedTime);

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

	LaunchBallEvtData *launchBall = new LaunchBallEvtData();
	humanView->keyboardHandler->bind(sf::Keyboard::Space, (IEventData*)launchBall);
}