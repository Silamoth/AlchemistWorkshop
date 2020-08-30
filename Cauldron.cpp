#include <algorithm>
#include "Cauldron.hpp"

Cauldron::Cauldron()
{
	cauldronOuterTexture = new sf::Texture();
	if (!cauldronOuterTexture->loadFromFile("Artwork/CauldronOuter.png"))
	{
		throw 2;
		return;
	}

	cauldronOuter.setTexture(*cauldronOuterTexture);
	
	std::vector<std::string> cycleNames;
	std::vector<int> framesPerCycle;
	cycleNames.push_back("idle");
	framesPerCycle.push_back(1);
	//cauldronInner.setupCycles(cycleNames, framesPerCycle);
	cauldronInner = AnimatedSprite(1, 12, "Artwork/CauldronInner.png", cycleNames, framesPerCycle);

	cauldronOuter.setPosition(sf::Vector2f(300, 100));
	cauldronOuter.setScale(sf::Vector2f(43, 43));
	cauldronInner.setScale(sf::Vector2f(43, 43));

	cauldronInner.setPosition(sf::Vector2f(cauldronOuter.getPosition().x + 9 * cauldronOuter.getScale().x, cauldronOuter.getPosition().y + 4 * cauldronOuter.getScale().y));
	//liquidPosition.x += 10 * cauldronInner.getSprite().getScale().x;
	//liquidPosition.y += 5 * cauldronInner.getSprite().getScale().y;

	//sf::Vector2f liquidSize = sf::Vector2f(9 * cauldronInner.getSprite().getScale().x, 8 * cauldronInner.getSprite().getScale().y);

	//liquidRect = new sf::FloatRect(liquidPosition, liquidSize);

	sf::Vector2f size = sf::Vector2f(cauldronInner.getSprite().getTexture()->getSize());
	size.x *= cauldronInner.getSprite().getScale().x - 10;
	size.y *= cauldronInner.getSprite().getScale().y - 10;

	sf::Vector2f position = cauldronInner.getPosition();
	position.x += 2 * cauldronInner.getSprite().getScale().x;
	position.y += 2 * cauldronInner.getSprite().getScale().y;

	rect = new sf::FloatRect(position, size);

	//Color stuff
	cauldronInner.setColor(sf::Color(255, 255, 255, 128));
	//std::cout << (int)(getColor().r) << std::endl;
}

std::vector<sf::Sprite> Cauldron::getIngredientSprites()
{
	std::vector<sf::Sprite> ingredientSprites;
	for (auto it = ingredients.begin(); it != ingredients.end(); it++)
	{
		auto x = it->getSprite();
		ingredientSprites.push_back(it->getSprite());
	}

	//for (auto ing : ingredientSet)
		//ingredientSprites.push_back(ing.getSprite());

	return ingredientSprites;
}

void Cauldron::addIngredient(Ingredient ingredient) 
{ 
	ingredients.push_back(ingredient);
	ingredientNames.insert(ingredient.getName());
	//ingredientSet.insert(ingredient);

	//Determine new color for mixture in cauldron

	int r = 0, g = 0, b = 0;

	for (auto it = ingredients.begin(); it != ingredients.end(); it++)
	{
		r += it->getColor().r;
		g += it->getColor().g;
		b += it->getColor().b;
	}

	r /= ingredients.size();
	g /= ingredients.size();
	b /= ingredients.size();

	cauldronInner.setColor(sf::Color(r, g, b, 128));
}

bool Cauldron::checkRecipe(Recipe recipe)
{
	return ingredientNames == recipe.getIngredientNamesSet();

	//std::cout << recipe.getIngredientNames().size() << " ?= " << ingredients.size() << std::endl;
	if (recipe.getIngredientNames().size() != ingredients.size())
		return false;

	for (auto it = ingredients.begin(); it != ingredients.end(); it++)
	{
		if (std::find(recipe.getIngredientNames().begin(), recipe.getIngredientNames().end(), it->getName()) == recipe.getIngredientNames().end())
		{
			return false;
			std::cout << "Couldn't find ingredient with name " << it->getName() << std::endl;
		}
	}

	return true;
}

void Cauldron::clearIngredients()
{ 
	ingredients.clear();
	cauldronInner.setColor(sf::Color(255, 255, 255, 128));
	//ingredientSet.clear();
}
