#include <SFML/OpenGL.hpp>
// FOR TESTING, REMOVE LATER

#include "GameState.h"
#include "Event.h"

void GameOverState::init()
{
	timer = 0;
	winner = 0;
	humanView = new HumanView(window);
	EventManager::get()->addListener(this, GAME_OVER);
}

void GameOverState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	string playerColor;
	bm::Color strColor;
	int xOffset;
	if (winner == 1)
	{
		playerColor = "Green";
		strColor = bm::Color(100, 255, 120, 80);
		xOffset = 80;
	}
	else
	{
		playerColor = "Blue";
		strColor = bm::Color(100, 200, 255, 80);
		xOffset = 100;
	}

	string winnerStr = "Game over. " + playerColor + " player wins!";

	humanView->drawText(winnerStr, Vec2D<double>(xOffset, 250), strColor, "arial", 48);
	
	timer += elapsedTime;

	if (timer > 5)
	{
		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("main_menu", "game_over", true);

		EventManager::get()->queueEvent((IEventData*)data);
	}
}

void GameOverState::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case GAME_OVER:
		onGameOver((GameOverEvtData*)e);
	}
}

void GameOverState::onGameOver(GameOverEvtData *event)
{
	winner = event->getWinner();
}

