
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "GameState.h"

// TESTING TINYXML
#include "tinyxml2.h"
void TestXml();

using namespace std;

bool handleEvent(sf::Event event);
void initEventManager();
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
	initEventManager();
	initGameState();

    // Start main loop
    bool Running = true;

	double elapsedTime = 0;

	//TINYXML TESTING
	TestXml();

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

		// Handle game events
		EventManager::get()->update();	

		// Update game state
		StateManager::get()->getCurrentState()->update(elapsedTime);


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


void TestXml()
{
	static const char* xml = 
        "<?xml version=\"1.0\"?>"
        "<!DOCTYPE PLAY SYSTEM \"play.dtd\">"
        "<PLAY>"
        "<TITLE>A Midsummer Night's Dream</TITLE>"
        "</PLAY>";

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile("test.xml") != tinyxml2::XML_NO_ERROR)
	{
		cout << "Error" << endl;
	}
	else
	{
		tinyxml2::XMLElement *visual = doc.FirstChildElement("Actor")->FirstChildElement("VisualComponent");
		tinyxml2::XMLElement *texture = visual->FirstChildElement("Texture");
		const char *tText = texture->GetText();

		tinyxml2::XMLElement *pos = visual->FirstChildElement("Position");
		int x = pos->IntAttribute("x");
		int y = pos->IntAttribute("y");
		int z = pos->IntAttribute("z");

		cout << "Texture: " << tText << endl;
		cout << "Position: (" << x << ", " << y << ", " << z << ")" << endl;
	}
}

