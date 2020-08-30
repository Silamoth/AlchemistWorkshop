#include "EndOfDayMenu.hpp"

EndOfDayMenu::EndOfDayMenu()
{
	font = new sf::Font();
	font->loadFromFile("ZillaSlab-Regular.ttf");

	nextDayRect = sf::FloatRect(900, 700, 185, 100);
	nextDayText.setPosition(sf::Vector2f(nextDayRect.left, nextDayRect.top));

	nextDayText.setString("Next Day");
	nextDayText.setFillColor(sf::Color::Blue);
	nextDayText.setCharacterSize(50);
	nextDayText.setFont(*font);

	summaryText.setPosition(sf::Vector2f(nextDayRect.left - 340, nextDayRect.top - 150));
	summaryText.setString("You made ___ gold by selling potions today.");
	summaryText.setFillColor(sf::Color::Black);
	summaryText.setCharacterSize(50);
	summaryText.setFont(*font);

	movedOn = false;
}

void EndOfDayMenu::update(Hand* hand)
{
	if (hand->getCanInteract() && !hand->getHoldingItem())
	{
		if (hand->getRect().intersects(nextDayRect) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			hand->interact();
			movedOn = true;
		}
	}
}

std::vector<sf::Text> EndOfDayMenu::getText()
{
	std::vector<sf::Text> text;

	text.push_back(nextDayText);
	text.push_back(summaryText);

	return text;
}
