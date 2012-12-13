#include <SFML/OpenGL.hpp>
// FOR TESTING, REMOVE LATER

#include "GameState.h"
#include "Event.h"

void InnerGameState::init()
{
	timer = 0;
	humanView = new HumanView();
}

void InnerGameState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

	timer += elapsedTime;

	if (timer > 0.33)
	{
		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("game_over", "inner_game", true);

		EventManager::get()->queueEvent((IEventData*)data);
	}

}
