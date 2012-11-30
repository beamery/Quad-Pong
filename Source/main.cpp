
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "GameState.h"
#include "Global.h"

using namespace std;

bool handleEvent(sf::Event event);
void initGameState();

////////////////////////////////////////////////////////////////////////////////
// Main Entry point of application
////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Create the main window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	sf::Window window(sf::VideoMode(800, 600, 32), "Quad Pong", sf::Style::Default, settings);
	sf::Clock clock;

	// Initialize game data
	initGameState();

    // Start main loop
    bool Running = true;

	double elapsedTime = 0;
    while (Running)
    {
		// Get new elapsed time
		elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();


		// Handle system events
		sf::Event event;
		while (window.pollEvent(event))
		{
			Running = handleEvent(event);
		}

		// TODO: Handle game events

		// Update game state
		stateManager->getCurrentState()->update(elapsedTime);


		// RENDERING CODE FOR TESTING, REMOVE LATER
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		{
			glColor3f(0.2f, 0.2f, 0.8f);
			glVertex2f(-0.25f, -0.25f);
			glColor3f(0.8f, 0.2f, 0.2f);
			glVertex2f(0.25f, -0.25f);
			glColor3f(0.2f, 0.8f, 0.2f);
			glVertex2f(0.0f, 0.25f);
		}
		glEnd();

		window.display();
    }
	
    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
// Initialize our state manager, called once at program startup
////////////////////////////////////////////////////////////////////////////////
void initGameState()
{
	MainMenuState *mainMenu = new MainMenuState();
	InnerGameState *innerGame = new InnerGameState();
	GameOverState *gameOver = new GameOverState();

	stateManager->addState("main_menu", mainMenu);
	stateManager->addState("inner_game", innerGame);
	stateManager->addState("game_over", gameOver);

	stateManager->changeState("main_menu");
}

////////////////////////////////////////////////////////////////////////////////
// Handle system events, called each frame.
////////////////////////////////////////////////////////////////////////////////
bool handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed)
		return false;
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		return false;
	else if (event.type == sf::Event::Resized)
	{
		// adjust the viewport when the window is resized
		glViewport(0, 0, event.size.width, event.size.height);
	}
	return true;
}

