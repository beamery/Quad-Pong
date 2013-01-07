#include "Actor.h"

void ScoreboardComponent::postInit()
{
	EventManager::get()->addListener((IEventListener*)this, SCORE);
	reset();
}

void ScoreboardComponent::reset()
{
	p1Score = 0;
	p2Score = 0;
}

void ScoreboardComponent::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case SCORE:
		onScore((ScoreEvtData*)e);
	}
}

void ScoreboardComponent::onScore(ScoreEvtData *event)
{
	if (event->getScorer() == 1)
		p1Score++;
	else
		p2Score++;
}