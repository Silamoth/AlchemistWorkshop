#ifndef recipeHeader
#define recipeHeader

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>

class Recipe
{
	public:
		//static bool compareStrings(std::string a, std::string b) { return a == b; }

	private:
		std::string potionName;
		std::vector<std::string> ingredientNames;
		sf::Color potionColor;
		//std::set<Ingredient, decltype(Ingredient::compareIngredients)*> ingredientSet;
		bool compareStrings(std::string a, std::string b) { return a > b; }
		std::set<std::string> ingredientNamesSet;

	public:
		Recipe(std::string potionName, std::vector<std::string> ingredientNames, sf::Color color);
		Recipe(std::string potionName, std::set<std::string> ingredientNames, sf::Color color);
		std::string getPotionName() { return potionName; }
		std::vector<std::string> getIngredientNames() { return ingredientNames; }
		sf::Color getColor() { return potionColor; }
		//std::set<Ingredient, decltype(Ingredient::compareIngredients)*> getIngredientSet() { return ingredientSet; }
		std::set<std::string> getIngredientNamesSet() { return ingredientNamesSet; }
};

#endif
