#ifndef EndOfDayMenuHeader
#define EndOfDayMenuHeader

#include <SFML/Graphics.hpp>
#include <vector>
#include "Hand.hpp"

class EndOfDayMenu
{
	private:
		sf::FloatRect nextDayRect;
		sf::Text summaryText, nextDayText;
		bool movedOn;
		sf::Font* font;

	public:
		EndOfDayMenu();

		void update(Hand* hand);
		bool getMovedOn() { return movedOn; }

		std::vector<sf::Text> getText();
		void reset() { movedOn = false; }
};

#endif
