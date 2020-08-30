#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter(int num, int life)
{
	//ParticleEmitter::spawnPosition = spawnPosition;
	particleTexture = new sf::Texture();
	particleLife = life;

	if (!particleTexture->loadFromFile("Artwork/Particle.png"))
	{
		std::cout << "Error: could not load particle texture" << std::endl;
		throw 2;
		return;
	}

	initializeParticles(num);
}

void ParticleEmitter::update(sf::Time delta)
{
	//std::vector<Particle> newParticles;
	for (auto it = particles.begin(); it != particles.end(); it++)
	{
		it->update(delta);

		//Only keep particles that have life remaining
		//if (it->getLife() > 0)
			//newParticles.push_back(*it);
		//else
			//std::cout << "This particle go bye bye" << std::endl;
	}

	//particles = newParticles;
}

void ParticleEmitter::initializeParticles(int num)
{
	for (int i = 0; i < num; i++)
	{
		Particle newParticle = Particle(particleTexture, particleLife);
		particles.push_back(newParticle);
	}
}

void ParticleEmitter::randomizeParticles(sf::Vector2f spawnPosition, sf::Color color)
{
	for (auto it = particles.begin(); it != particles.end(); it++)
	{
		int spawnX = (rand() % 100) - 50;
		int spawnY = (rand() % 100) - 50;
		int velY = -1 * (rand() % 800) - 60;

		//std::cout << "Is particle active? " << it->isActive() << std::endl;
		if (!(it->isActive()))
		{
			sf::Vector2f particlePosition = spawnPosition;
			//particlePosition.x += spawnX;
			particlePosition.y += spawnY;

			particlePosition.x = spawnPosition.x + (rand() % 40) - 20;
			particlePosition.y += (rand() % 10) - 5;

			sf::Vector2f velocity = sf::Vector2f(0, 0);
			//velocity.x = (rand() % 2000) - 1000;
			velocity.y = velY /**- (rand() % 3)**/;

			it->setPosition(particlePosition);
			it->setVelocity(velocity);
			it->setColor(color);
			it->setLife(particleLife);

			//std::cout << "Particle randomized" << std::endl;
		}
	}
}

void ParticleEmitter::emitParticles()
{
	for (auto it = particles.begin(); it != particles.end(); it++)
	{
		it->activate();
	}
}

std::vector<sf::Sprite> ParticleEmitter::getParticleSprites()
{
	std::vector<sf::Sprite> sprites;

	for (auto it = particles.begin(); it != particles.end(); it++)
	{
		if (it->isActive())
			sprites.push_back(it->getSprite());
	}

	return sprites;
}
