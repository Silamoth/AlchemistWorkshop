#include "GrabbableObject.hpp"

GrabbableObject::GrabbableObject()
{

}

GrabbableObject::GrabbableObject(int numFrames, int frameWidth, std::string name)
{
	GrabbableObject::name = name;
	animSprite = AnimatedSprite(numFrames, frameWidth, name);
	setRect();
}

void GrabbableObject::setRect()
{
	sf::Vector2f size = sf::Vector2f(animSprite.getSprite().getTexture()->getSize());
	size.x *= animSprite.getSprite().getScale().x;
	size.y *= animSprite.getSprite().getScale().y;

	sf::Vector2f position = sf::Vector2f(animSprite.getPosition());
	//position.x *= sprite.getScale().x;
	//position.y *= sprite.getScale().y;

	rect = new sf::FloatRect(position, size);
}

void GrabbableObject::setPosition(sf::Vector2f newPos)
{
	animSprite.setPosition(newPos);
	setRect();
}
