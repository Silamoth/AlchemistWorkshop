#include "Ingredient.hpp"

Ingredient::Ingredient(std::string name, sf::Color color) : GrabbableObject(1, 32, "Artwork/Ingredients/" + name + ".png")
{
	Ingredient::name = name;
	Ingredient::color = color;

	//texture = new sf::Texture();

	/**if (!texture->loadFromFile("Artwork/Ingredients/" + name + ".png"))
	{
		throw 2;	//Texture not found
		return;
	}**/

	std::vector<std::string> cycleNames;
	std::vector<int> framesPerCycle;

	cycleNames.push_back("idle");
	framesPerCycle.push_back(1);
	animSprite.setupCycles(cycleNames, framesPerCycle);

	//animSprite.setTexture(*texture);
	animSprite.setScale(sf::Vector2f(4, 4));

	setRect();
}

void Ingredient::update()
{

}

bool Ingredient::compareIngredients(Ingredient ingOne, Ingredient ingTwo)
{
	return ingOne.getName().compare(ingTwo.getName());
}
