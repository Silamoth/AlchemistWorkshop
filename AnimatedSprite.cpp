#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(int numFrames, int frameWidth, std::string spritesheetPath, std::vector<std::string> cycleNames, std::vector<int> framesPerCycle)
{
	loadBasics(numFrames, frameWidth, spritesheetPath);

	setupCycles(cycleNames, framesPerCycle);

	//std::cout << spritesheetPath << ": " << cycles[0].getNumFrames() << std::endl;
	setCycle(cycleNames[0]);
}

AnimatedSprite::AnimatedSprite(int numFrames, int frameWidth, std::string spritesheetPath)
{
	loadBasics(numFrames, frameWidth, spritesheetPath);
}

void AnimatedSprite::loadBasics(int numFrames, int frameWidth, std::string spritesheetPath)
{
	AnimatedSprite::numFrames = numFrames;
	AnimatedSprite::frameWidth = frameWidth;

	texture = new sf::Texture();
	if (!texture->loadFromFile(spritesheetPath))
	{
		std::cout << "error" << std::endl;
		//throw 2;	//File not found
		return;
	}

	sprite.setTexture(*texture);
	sprite.setScale(sf::Vector2f(3, 3));

	setCurrentFrame(0);
}

void AnimatedSprite::setCurrentFrame(int newFrame)
{
	currentFrame = newFrame;
	sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, sprite.getTexture()->getSize().y));
}

void AnimatedSprite::update(sf::Time delta)
{
	cycles[currentCycle].update(delta);
	currentFrame = cycles[currentCycle].getPreviousFrames() + cycles[currentCycle].getCurrentFrame();
}

void AnimatedSprite::setCycle(std::string name)
{
	for (int i = 0; i < cycles.size(); i++)
	{
		if (cycles[i].getName() == name)
		{
			currentCycle = i;
			setCurrentFrame(cycles[currentCycle].getPreviousFrames() + cycles[currentCycle].getCurrentFrame());
		}
	}
}

void AnimatedSprite::setupCycles(std::vector<std::string> cycleNames, std::vector<int> framesPerCycle)
{
	AnimationCycle first(framesPerCycle[0], 0, cycleNames[0]);
	cycles.push_back(first);

	for (int i = 1; i < cycleNames.size(); i++)
	{
		AnimationCycle c(framesPerCycle[i], cycles[i - 1].getPreviousFrames() + cycles[i - 1].getNumFrames(), cycleNames[i]);
		cycles.push_back(c);
	}
}

void AnimatedSprite::setScale(sf::Vector2f scale)
{
	AnimatedSprite::scale = scale;
	sprite.setScale(scale);
}

AnimatedSprite::~AnimatedSprite()
{
	//if (texture != nullptr)
		//delete texture;
}
