#include <SFML/OpenGL.hpp>
#include "Global.h"
// FOR TESTING, REMOVE LATER

#include "GameState.h"

void InnerGameState::init()
{
	timer = 0;
}

void InnerGameState::update(double elapsedTime)
{
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

	timer += elapsedTime;

	if (timer > 2)
		stateManager->changeState("game_over");

}
