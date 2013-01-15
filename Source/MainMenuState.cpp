#include <SFML/OpenGL.hpp>
// FOR TESTING, REMOVE LATER

#include "GameState.h"
#include "Event.h"

void MainMenuState::init()
{
	timer = 0;
	humanView = new HumanView(window);
}

void MainMenuState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	string line1 = "Press spacebar to launch ball.";
	string line2 = "The green player moves their paddles with WASD.";
	string line3 = "The blue player moves their paddles with the arrow keys.";
	humanView->drawText(line1, Vec2D<double>(25, 150), bm::Color(200, 200, 200, 255), "arial", 24);
	humanView->drawText(line2, Vec2D<double>(25, 250), bm::Color(200, 200, 200, 255), "arial", 24);
	humanView->drawText(line3, Vec2D<double>(25, 350), bm::Color(200, 200, 200, 255), "arial", 24);

	timer += elapsedTime;

	if (timer > 10)
	{
		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("inner_game", "main_menu", true);
		
		EventManager::get()->queueEvent((IEventData*)data);
	}

}
