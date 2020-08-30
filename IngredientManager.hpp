//This class will manage interactions between Hand, Ingredients, and (maybe) Cauldron
//Also holds ingredients available for use (for the moment, at least)

#include <vector>
#include "Ingredient.hpp"
#include "Hand.hpp"
#include "Cauldron.hpp"
#include "Spoon.hpp"
#include "Recipe.hpp"
#include "Potion.hpp"
#include "ParticleEmitter.hpp"
#include "BarArrow.hpp"

class IngredientManager
{
	private:
		std::vector<GrabbableObject*> availableObjects;
		sf::Texture* ingredientBarTexture;
		sf::Sprite ingredientBar;
		sf::FloatRect* barRect;
		std::vector<Recipe> recipes;

		bool hasPotion;
		Potion potion;

		Recipe* currentRecipe;
		bool hasRecipe;
		sf::Color cauldronStartingColor;

		ParticleEmitter particleEmitter;

		BarArrow rightArrow, leftArrow;
		int barOffset;
		int prevOffset;
		std::vector<bool> isObjectActive;	//One-to-one correspondence with availableObjects to check if active

	public:
		void update(Hand* hand, Cauldron* cauldron, Spoon* spoon, sf::Time delta);
		IngredientManager();

		sf::Sprite getIngredientBar() { return ingredientBar; }
		std::vector<sf::Sprite> getObjects();
		//sf::FloatRect getBarRect() { return barRect; }

		bool getHasPotion() { return hasPotion; }
		Potion getPotion() { return potion; }
};