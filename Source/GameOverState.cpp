#include <SFML/OpenGL.hpp>
#include "Global.h"
// FOR TESTING, REMOVE LATER

#include "GameState.h"

void GameOverState::init()
{
	timer = 0;
}

void GameOverState::update(double elapsedTime)
{
	glClearColor(0.4f, 0.2f, 0.2f, 1.0f);
	
	timer += elapsedTime;

	if (timer > 2)
		stateManager->changeState("main_menu");
}
