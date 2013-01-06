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
	glClearColor(0.2f, 0.4f, 0.2f, 1.0f);

	timer += elapsedTime;

	if (timer > 0.33)
	{
		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("inner_game", "main_menu", true);
		
		EventManager::get()->queueEvent((IEventData*)data);
	}

}
