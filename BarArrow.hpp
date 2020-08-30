#include <SFML/Graphics.hpp>
#include "Hand.hpp"

class BarArrow
{
	private:
		sf::Texture* texture;
		sf::Sprite sprite;
		int scrollAmount;
		sf::FloatRect rectangle;

	public:
		BarArrow() {}
		BarArrow(int scrollAmount, sf::Vector2f pos);
		int update(Hand* hand, int currOffset);

		sf::FloatRect getRect() { return rectangle; }
		sf::Sprite getSprite() { return sprite; }
};