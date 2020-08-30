#ifndef cauldronHeader
#define cauldronHeader

#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include "AnimatedSprite.hpp"
#include "Ingredient.hpp"
#include "Recipe.hpp"

class Cauldron
{
	private:
		sf::Texture* cauldronOuterTexture;
		sf::Sprite cauldronOuter;
		AnimatedSprite cauldronInner;
		std::vector<Ingredient> ingredients;
		sf::FloatRect* rect;

		bool compareStrings(std::string a, std::string b) { return a > b; }

		//Don't need ingredientSet; just track names for easy comparison
		//std::set<Ingredient, decltype(Ingredient::compareIngredients)*> ingredientSet;
		std::set<std::string> ingredientNames;

	public:
		Cauldron();
		void addIngredient(Ingredient ingredient);

		sf::Sprite getOuterSprite() { return cauldronOuter; }
		sf::Sprite getInnerSprite() { return cauldronInner.getSprite(); }

		sf::FloatRect getRect() { return *rect; }
		std::vector<sf::Sprite> getIngredientSprites();

		bool checkRecipe(Recipe recipe);
		void setColor(sf::Color color) { cauldronInner.setColor(color); }
		sf::Color getColor() { return cauldronInner.getColor(); }

		void clearIngredients();
};

#endif
