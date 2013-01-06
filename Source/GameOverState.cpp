#include <SFML/OpenGL.hpp>
// FOR TESTING, REMOVE LATER

#include "GameState.h"
#include "Event.h"

void GameOverState::init()
{
	timer = 0;
	humanView = new HumanView(window);
}

void GameOverState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.4f, 0.2f, 0.2f, 1.0f);
	
	timer += elapsedTime;

	if (timer > 0.33)
	{
		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("main_menu", "game_over", true);

		EventManager::get()->queueEvent((IEventData*)data);
	}

}
