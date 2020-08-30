#include "IngredientManager.hpp"
#include "StateManager.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1440), "Alchemist's Workshop (Pending)");
	window.setMouseCursorVisible(false);

	sf::Clock clock;

	Hand hand;
	Cauldron cauldron;
	IngredientManager ingManager;
	Spoon spoon(cauldron.getRect());

	StateManager stateManager;

	EndOfDayMenu endOfDayMenu;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

		//General update stuff
		sf::Time delta = clock.restart();
		auto localPos = sf::Mouse::getPosition(window);
		hand.update(delta, sf::Vector2f(localPos.x, localPos.y));

		if (stateManager.getState() == State::Brewing)
		{
			//Draw stuff
			window.draw(cauldron.getOuterSprite());
			window.draw(cauldron.getInnerSprite());

			window.draw(ingManager.getIngredientBar());

			std::vector<sf::Sprite> objects = ingManager.getObjects();
			for (auto it = objects.begin(); it != objects.end(); it++)
				window.draw(*it);

			if (hand.getHoldingItem())
				window.draw(hand.getHeldObject()->getSprite());

			window.draw(spoon.getSprite());

			ingManager.update(&hand, &cauldron, &spoon, delta);
			spoon.update();
		}
		else if (stateManager.getState() == State::EndOfDay)
		{
			//Drawing
			for (sf::Text text : endOfDayMenu.getText())
				window.draw(text);

			endOfDayMenu.update(&hand);
		}

		//Hand stuff always needs to happen and must go after everything to be displayed on top
		window.draw(hand.getSprite());

		window.display();
		
		stateManager.update(sf::Vector2f(localPos.x, localPos.y), delta, &endOfDayMenu);

		//clock.restart();
	}

	return 0;
}