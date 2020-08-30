#ifndef potionHeader
#define potionHeader

#include <SFML/Graphics.hpp>
#include "GrabbableObject.hpp"

class Potion : public GrabbableObject
{
	private:
		//sf::Texture* texture;
		//sf::Sprite sprite;
		std::string name;

	public:
		Potion(std::string name);
		Potion() {}
		~Potion();
		sf::Sprite getSprite() { return animSprite.getSprite(); }
		void update() override {}
};

#endif
