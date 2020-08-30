#include <iostream>
#include "StateManager.hpp"

StateManager::StateManager()
{
	state = State::Brewing;
}

void StateManager::update(sf::Vector2f mousePos, sf::Time delta, EndOfDayMenu* endMenu)
{
	//std::cout << state << std::endl;

	if (state == State::Brewing)
	{
		timeOfDay += delta.asSeconds();

		if (timeOfDay >= secondsInDay)
		{
			timeOfDay = 0;
			//state = State::EndOfDay;

			//Need to tell Hand to drop its held item onto IngredientManager's inventory bar
		}
	}
	else if (state == State::EndOfDay)
	{
		if (endMenu->getMovedOn())
		{
			state = State::Brewing;
			endMenu->reset();
		}
	}
	else if (state == State::MainMenu)
	{
		//TODO: Main menu stuff
	}
}
