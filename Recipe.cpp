#include "Recipe.hpp"

Recipe::Recipe(std::string potionName, std::vector<std::string> ingredientNames, sf::Color color)
{
	Recipe::potionName = potionName;
	Recipe::ingredientNames = ingredientNames;
	potionColor = color;
}

Recipe::Recipe(std::string potionName, std::set<std::string> ingredientNames, sf::Color color)
{
	Recipe::potionName = potionName;
	Recipe::ingredientNamesSet = ingredientNames;
	potionColor = color;
}
