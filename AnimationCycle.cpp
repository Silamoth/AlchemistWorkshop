#include "AnimationCycle.hpp"
#include <SFML/System.hpp>

AnimationCycle::AnimationCycle(int numFrames, int numPreviousFrames, std::string name)
{
	currentFrame = 0;
	currTime = 0;
	AnimationCycle::numFrames = numFrames;
	AnimationCycle::numPreviousFrames = numPreviousFrames;
	AnimationCycle::name = name;
}

void AnimationCycle::update(sf::Time delta)
{
	const int frameTime = 100;

	currTime += delta.asMilliseconds();

	if (currTime >= frameTime)
	{
		currentFrame++;
		currentFrame %= numFrames;
		currTime = 0;
	}
}