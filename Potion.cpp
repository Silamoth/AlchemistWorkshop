#include "Potion.hpp"

Potion::Potion(std::string name) : GrabbableObject(1, 32, "Artwork/Potions/" + name + ".png")
{
	Potion::name = name;

	/**texture = new sf::Texture();
	if (!texture->loadFromFile("Artwork/Potions/" + name + ".png"))
	{
		throw 2;
		return;
	}

	sprite.setTexture(*texture);
	sprite.setScale(sf::Vector2f(10, 10));
	sprite.setPosition(785, 350);**/

	std::vector<std::string> cycleNames;
	std::vector<int> framesPerCycle;

	cycleNames.push_back("idle");
	framesPerCycle.push_back(1);
	animSprite.setupCycles(cycleNames, framesPerCycle);

	//animSprite.setTexture(*texture);
	animSprite.setScale(sf::Vector2f(4, 4));
	animSprite.setPosition(sf::Vector2f(785, 350));

	setRect();
}

Potion::~Potion()
{
	//if (texture != NULL && texture != nullptr)
		//delete texture;
}
