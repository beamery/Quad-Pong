
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "GameState.h"
#include "Actor.h"

// TESTING
#include "tinyxml2.h"
void testXml();
void testActors();

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
	window.setKeyRepeatEnabled(false);
	sf::Clock clock;
	sf::Clock totalClock;

	// Initialize game data
	initEventManager();
	initGameState();

    // Start main loop
    bool Running = true;

	double elapsedTime = 0;
	double totalTime = 0;

	// TESTING CALLS
	testXml();
	testActors();

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
		StateManager::get()->getCurrentState()->update(totalTime, elapsedTime);


		// RENDERING CODE FOR TESTING, REMOVE LATER
		float r, g, b;
		background->update(totalTime, elapsedTime);
		((TestComponent2*)background->getComponent(TEST2))->getColor(r, g, b);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		{
			glColor3f(r, g, b);
			glVertex2f(-0.25f, -0.25f);
			glColor3f(b, g, r);
			glVertex2f(0.25f, -0.25f);
			glColor3f(g, r, b);
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


void testXml()
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
		cout << "Position: (" << x << ", " << y << ", " << z << ")" << endl << endl;
	}
}

void testActors()
{
	ActorFactory *af = new ActorFactory();
	Actor *a1 = af->createActor("test1.xml");
	Actor *a2 = af->createActor("test2.xml");
	Actor *a3 = af->createActor("test3.xml");
	Actor *a4 = af->createActor("test4.xml");

	a1->print();
	a2->print();
	a3->print();
	a4->print();
}


