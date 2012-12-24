
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "GameState.h"
#include "Actor.h"
#include "Tests.h"

using namespace std;

bool handleEvent(sf::Event event);
void initGL(int width, int height);
void initEventManager();
void initGameState();
void initTextures();

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
	window.setKeyRepeatEnabled(false);
	sf::Clock clock;
	sf::Clock totalClock;

	// Initialize game data
	initGL(window.getSize().x, window.getSize().y);
	initEventManager();
	initGameState();
	initTextures();

    // Start main loop
    bool Running = true;

	double elapsedTime = 0;
	double totalTime = 0;

	// TESTING CALLS
	testXml();
	testActors();
	testVectors();

	ActorFactory *af = new ActorFactory();
	Actor *background = af->createActor("test2.xml");
	// END TESTING

    while (Running)
    {
		// Get new elapsed time and total time
		elapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		totalTime = clock.getElapsedTime().asSeconds();


		// Handle system events
		sf::Event event;
		while (window.pollEvent(event))
		{
			Running = handleEvent(event); // STUB CODE, REMOVE LATER

			HumanView *v = StateManager::get()->getCurrentState()->getHumanView();

			// Have the human view handle input events
			switch(event.type)
			{
			case sf::Event::EventType::KeyPressed:
				v->keyboardHandler->onKeyDown(event); break;
			case sf::Event::EventType::KeyReleased:
				v->keyboardHandler->onKeyUp(event); break;
			case sf::Event::EventType::MouseButtonPressed:
				v->pointerHandler->onPointerButtonDown(event); break;
			case sf::Event::EventType::MouseButtonReleased:
				v->pointerHandler->onPointerButtonUp(event); break;
			case sf::Event::EventType::MouseWheelMoved:
				v->pointerHandler->onWheelMove(event); break;
			case sf::Event::EventType::MouseMoved:
				v->pointerHandler->onPointerMove(event, window); break;
			default:
				Running = handleEvent(event);
			}
		}

		// Handle game events
		EventManager::get()->update();	

		// Update game state
		glClear(GL_COLOR_BUFFER_BIT);
		StateManager::get()->getCurrentState()->update(totalTime, elapsedTime);

		// RENDERING CODE FOR TESTING, REMOVE LATER
		//drawSprite();
		//drawTriangle(background, totalTime, elapsedTime);
		//drawCircle(Mouse::getPosition(window).x, Mouse::getPosition(window).y, 70, 360);

		window.display();
    }
	
    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
// Initialize our OpenGL context for this window, called once at startup.
////////////////////////////////////////////////////////////////////////////////
void initGL(int width, int height)
{
    //Set the viewport
	glViewport(0, 0, width, height);

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, width, height, 0, 1, -1);

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

////////////////////////////////////////////////////////////////////////////////
// Initialize our event manager, called once at program startup
////////////////////////////////////////////////////////////////////////////////
void initEventManager()
{
	EventManager *eventManager = new EventManager(true, "Main Event Manager");
}



////////////////////////////////////////////////////////////////////////////////
// Initialize our state manager, called once at program startup
////////////////////////////////////////////////////////////////////////////////
void initGameState()
{
	StateManager *stateManager = new StateManager(true);
	EventManager::get()->addListener((IEventListener*)stateManager);

	MainMenuState *mainMenu = new MainMenuState();
	InnerGameState *innerGame = new InnerGameState();
	GameOverState *gameOver = new GameOverState();

	StateManager::get()->addState("main_menu", mainMenu);
	StateManager::get()->addState("inner_game", innerGame);
	StateManager::get()->addState("game_over", gameOver);

	StateManager::get()->changeState("main_menu");
}

////////////////////////////////////////////////////////////////////////////////
// Initialize our texture manager, called once at program startup
////////////////////////////////////////////////////////////////////////////////
void initTextures()
{
	TextureManager *textureManager = new TextureManager(true);

	TextureManager::get()->loadTexture("../Assets/SpriteLogo.jpg", "sprite_logo");
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

