#ifndef Ingr
#define Ingr

#include <SFML/Graphics.hpp>
#include "GrabbableObject.hpp"

class Ingredient : public GrabbableObject
{
	private:
		//sf::Texture* texture;
		//sf::Sprite sprite;
		//std::string name;
		sf::Color color;

	public:
		Ingredient(std::string name, sf::Color);
		Ingredient() : GrabbableObject() {};
		//Ingredient(const GrabbableObject& obj) : GrabbableObject(obj) {}
		
		sf::Sprite getSprite() { return animSprite.getSprite(); }
		std::string getName() { return name; }
		sf::Color getColor() { return color; }
		void update() override;

		static bool compareIngredients(Ingredient ingOne, Ingredient ingTwo);
};

#endif