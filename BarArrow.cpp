#include "BarArrow.hpp"

BarArrow::BarArrow(int scrollAmount, sf::Vector2f pos)
{
	BarArrow::scrollAmount = scrollAmount;

	texture = new sf::Texture();

	if (scrollAmount > 0)
		texture->loadFromFile("Artwork/ArrowRight.png");
	else
		texture->loadFromFile("Artwork/ArrowLeft.png");

	sprite.setTexture(*texture);
	sprite.setPosition(pos);
	sprite.setScale(3, 3);
	
	rectangle = sf::FloatRect(pos.x, pos.y, texture->getSize().x * sprite.getScale().x, texture->getSize().y * sprite.getScale().y);
}

int BarArrow::update(Hand* hand, int currOffset)
{
	if (hand->getCanInteract() && !hand->getHoldingItem())
	{
		if (rectangle.intersects(hand->getRect()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			hand->interact();
			return currOffset + scrollAmount;
		}
	}

	return currOffset;
}
