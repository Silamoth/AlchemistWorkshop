#ifndef grabbableHeader
#define grabbableHeader

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

class GrabbableObject
{
	private:


	protected:
		AnimatedSprite animSprite;
		std::string name;
		sf::FloatRect* rect;
		void setRect();


	public:
		GrabbableObject();
		GrabbableObject(int numFrames, int frameWidth, std::string name);
		//GrabbableObject(const GrabbableObject& obj) { *this = obj; }
		sf::Sprite getSprite() { return animSprite.getSprite(); }
		std::string getName() { return name; }
		sf::FloatRect getRect() { return *rect; }
		//virtual void setPosition(sf::Vector2f newPos) = 0;
		virtual void update() = 0;
		void setPosition(sf::Vector2f newPos);
		
};

#endif
