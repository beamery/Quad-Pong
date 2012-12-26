#include "Input.h"
#include "Event.h"

void PointerHandler::onPointerMove(Event e, Window &w) 
{
	//std::cout << "Mouse at (" << Mouse::getPosition(w).x << ", " << Mouse::getPosition(w).y << ")" << std::endl;
	int x = Mouse::getPosition(w).x;
	int y = Mouse::getPosition(w).y;
	MousePositionEvtData *data = new MousePositionEvtData(x, y);
	EventManager::get()->queueEvent((IEventData*)data);
}

void PointerHandler::onPointerButtonDown(Event e)
{
	std::cout << getButtonName(e.mouseButton.button) << " pressed" << std::endl;
}

void PointerHandler::onPointerButtonUp(Event e)
{
	std::cout << getButtonName(e.mouseButton.button) << " released" << std::endl;
}

void PointerHandler::onWheelMove(Event e)
{
	std::cout << "Mouse wheel moved " << e.mouseWheel.delta << std::endl;
}


const char * PointerHandler::getButtonName(const sf::Mouse::Button button)
{
	switch (button)
	{
	default:
	case sf::Mouse::Left:
		return "Left Mouse Button";
	case sf::Mouse::Right:
		return "Right Mouse Button";
	case sf::Mouse::Middle:
		return "Middle Mouse Button";
	}

}
