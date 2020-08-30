#ifndef spoonHeader
#define spoonHeader

#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "GrabbableObject.hpp"

class Spoon : public GrabbableObject
{
	private:
		//AnimatedSprite animSprite;
		sf::FloatRect cauldronRect;
		float currentAngle;
		int stirCount;
		sf::Vector2f prevPoint;
		sf::Vector2f cauldronCenter;

	public:
		Spoon(sf::FloatRect cauldronRect);
		//sf::Sprite getSprite() { return animSprite.getSprite(); }
		void update();
		//void setPosition(sf::Vector2f newPos);
		int getStirCount() { return stirCount; }
		void resetStirCount();

		float getStirValue() { return 4.6949; }
		float getCurrentAngle() { return currentAngle; }
};

#endif
