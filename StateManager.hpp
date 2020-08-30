#ifndef StateManagerHeader
#define StateManagerHeader

#include <SFML/Graphics.hpp>
#include "EndOfDayMenu.hpp"

enum State { MainMenu, Brewing, EndOfDay };

class StateManager
{
	private:
		State state;
		float timeOfDay;	//1 day in the game will be...2 minutes in real life; measured in seconds
		const int secondsInDay = 10;

	public:
		StateManager();

		State getState() { return state; }
		void setState(State newState) { state = newState; }

		void update(sf::Vector2f mousePos, sf::Time delta, EndOfDayMenu* endMenu);
};

#endif
