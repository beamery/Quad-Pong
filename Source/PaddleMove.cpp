#include "Event.h"

// Event Data
PaddleMoveEvtData::PaddleMoveEvtData(int player, Direction dir, bool start) :
	IEventData(PADDLE_MOVE, "Paddle movement"),
	player(player), dir(dir), start(start) {}


// Event Listener
void PaddleMoveListener::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case PADDLE_MOVE:
		onPaddleMove((PaddleMoveEvtData*)e);
	}
}