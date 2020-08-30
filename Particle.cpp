#include "Particle.hpp"

Particle::Particle(sf::Texture* texture, sf::Vector2f velocity, int life, sf::Vector2f position)
{
	sprite.setTexture(*texture);
	Particle::velocity = velocity;
	Particle::life = life;
	sprite.setPosition(position);
	active = false;
}

Particle::Particle(sf::Texture* texture, int life)
{
	sprite.setTexture(*texture);
	Particle::life = life;
	sprite.setScale(sf::Vector2f(1.5, 1.5));
	active = false;
}

void Particle::update(sf::Time delta)
{
	sprite.setPosition(sf::Vector2f(sprite.getPosition().x + velocity.x * delta.asSeconds(), sprite.getPosition().y + velocity.y * delta.asSeconds()));
	life -= (int)(delta.asMilliseconds());
	
	if (life <= 0)
	{
		active = false;
		//std::cout << "Particle is no longer active..." << std::endl;
	}
}
