#ifndef ASprite
#define ASprite

#include <iostream>
#include <SFML/Graphics.hpp>
#include "AnimationCycle.hpp"

class AnimatedSprite
{
	private:
		sf::Texture *texture;
		sf::Sprite sprite;
		int numFrames, currentFrame, frameWidth;

		int currentCycle;
		std::vector<AnimationCycle> cycles;

		sf::Vector2f scale;

		void loadBasics(int numFrames, int frameWidth, std::string spritesheetPath);

	public:
		int getFrames() { return numFrames; }
		int getCurrentFrame() { return currentFrame; }
		void setCurrentFrame(int newFrame);	//0-indexed

		AnimatedSprite(int numFrames, int frameWidth, std::string spritesheetPath, std::vector<std::string> cycleNames, std::vector<int> framesPerCycle);
		AnimatedSprite(int numFrames, int frameWidth, std::string spritesheetPath);
		AnimatedSprite() {}

		sf::Vector2f getPosition() { return sprite.getPosition(); }
		void setPosition(sf::Vector2f newPosition) { sprite.setPosition(newPosition); }

		sf::Sprite getSprite() { return sprite; }

		void update(sf::Time delta);
		void setCycle(std::string name);

		void setupCycles(std::vector<std::string> cycleNames, std::vector<int> framesPerCycle);
		~AnimatedSprite();

		void setScale(sf::Vector2f scale);
		void setColor(sf::Color color) { sprite.setColor(color); }
		sf::Color getColor() { return sprite.getColor(); }
};

//Currently, this class assumes spritesheet is one row of equally-sized sprites

#endif