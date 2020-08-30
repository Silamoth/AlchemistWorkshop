#include "EmptyPotion.hpp"

EmptyPotion::EmptyPotion() : GrabbableObject(1, 32, "Artwork/Potions/emptyPotion.png")
{
	std::vector<std::string> cycleNames;
	std::vector<int> framesPerCycle;

	cycleNames.push_back("idle");
	framesPerCycle.push_back(1);
	animSprite.setupCycles(cycleNames, framesPerCycle);

	//animSprite.setTexture(*texture);
	animSprite.setScale(sf::Vector2f(4, 4));

	setRect();
}
