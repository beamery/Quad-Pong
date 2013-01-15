#include "Pong.h"

void Match::init() 
{
	volley = new Volley(humanView);
	scoreboard = ActorFactory::get()->createActor("Scoreboard.xml");
	EventManager::get()->addListener(this, MATCH_OVER);
}

void Match::update(double totalTime, double elapsedTime)
{
	ScoreboardComponent *sb = (ScoreboardComponent*)scoreboard->getComponent(SCOREBOARD);
	humanView->drawText(std::to_string(sb->getP1Score()), Vec2D<double>(25, 0), bm::Color(100, 255, 120, 80), "arial", 100);
	humanView->drawText(std::to_string(sb->getP2Score()), Vec2D<double>(650, 450), bm::Color(100, 200, 255, 80), "arial", 100);

	volley->update(totalTime, elapsedTime);

	// If someone reaches 11 points, they win
	int p1 = sb->getP1Score();
	int p2 = sb->getP2Score();
	if (p1 >= 3 && p1 > p2 + 1)
	{
		MatchOverEvtData *e = new MatchOverEvtData(1);
		EventManager::get()->queueEvent((IEventData*)e);
	}
	else if (p2 >= 3 && p2 > p1 + 1)
	{
		MatchOverEvtData *e = new MatchOverEvtData(2);
		EventManager::get()->queueEvent((IEventData*)e);
	}
}

void Match::processEvent(IEventData *e)
{
	switch (e->getEventType())
	{
	case MATCH_OVER:
		cout << "derp" << endl;
		onMatchOver((MatchOverEvtData*)e);
		break;
	}
}

void Match::onMatchOver(MatchOverEvtData *event)
{
	ChangeGameStateEvtData *gameStateData = 
		new ChangeGameStateEvtData("game_over", "inner_game", true);

	GameOverEvtData *gameOverData = new GameOverEvtData(event->getWinner());

	EventManager::get()->queueEvent((IEventData*)gameStateData);
	EventManager::get()->queueEvent((IEventData*)gameOverData);
}
