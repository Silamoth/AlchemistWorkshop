#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.hpp"

class ParticleEmitter
{
	private:
		//sf::Vector2f spawnPosition;
		std::vector<Particle> particles;
		sf::Texture* particleTexture;
		void initializeParticles(int num);
		int particleLife;

	public:
		ParticleEmitter() {}
		ParticleEmitter(int num, int life);
		void update(sf::Time delta);
		void emitParticles();
		void randomizeParticles(sf::Vector2f spawnPosition, sf::Color color);
		std::vector<sf::Sprite> getParticleSprites();
};