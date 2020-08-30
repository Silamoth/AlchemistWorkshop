#include <SFML/Graphics.hpp>
#include <iostream>

class Particle
{
	private:
		int life;
		sf::Sprite sprite;
		sf::Vector2f velocity;
		bool active;

	public:
		Particle(sf::Texture* texture, int life);
		Particle(sf::Texture* texture, sf::Vector2f velocity, int life, sf::Vector2f position);
		int getLife() { return life; }
		sf::Vector2f getPosition() { return sprite.getPosition(); }
		void setPosition(sf::Vector2f position) { sprite.setPosition(position); }
		sf::Sprite getSprite() { return sprite; }
		void setTexture(sf::Texture texture) { sprite.setTexture(texture); }

		void update(sf::Time delta);
		void activate() { active = true; }
		bool isActive() { return active; }
		
		void setVelocity(sf::Vector2f newVel) { velocity = newVel; }
		void setColor(sf::Color color) { sprite.setColor(color); }
		void setLife(int newLife) { life = newLife; }
};