#include <SFML/OpenGL.hpp>
// FOR TESTING, REMOVE LATER

#include "GameState.h"
#include "Event.h"
#include "Actor.h"

void InnerGameState::init()
{
	timer = 0;
	humanView = new HumanView();
	ActorFactory af;
	me = af.createActor("TestPhysVis.xml");
	((PhysicalComponent*)me->getComponent(PHYSICAL))->addImpulse(Vec2D<double>(50, 50));
}

void InnerGameState::update(double totalTime, double elapsedTime)
{
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

	timer += elapsedTime;
	
	me->update(totalTime, elapsedTime);
	humanView->drawActor(me);

	if (timer > 10)
	{
		ChangeGameStateEvtData *data = 
			new ChangeGameStateEvtData("game_over", "inner_game", true);

		EventManager::get()->queueEvent((IEventData*)data);
	}

}
