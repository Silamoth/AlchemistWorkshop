#include <SFML/System.hpp>

class AnimationCycle
{
	private:
		int currentFrame;
		int currTime;
		int numFrames;
		int numPreviousFrames;
		std::string name;
		//const int frameTime = 50;

	public:
		void update(sf::Time delta);
		AnimationCycle(int numFrames, int numPreviousFrames, std::string name);
		int getCurrentFrame() { return currentFrame; }
		int getPreviousFrames() { return numPreviousFrames; }
		int getNumFrames() { return numFrames; }
		std::string getName() { return name; }
};