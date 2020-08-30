#include "Spoon.hpp"

Spoon::Spoon(sf::FloatRect cauldronRect) : GrabbableObject(1, 10, "Artwork/Spoon.png")
{
	//animSprite = AnimatedSprite(1, 10, "Artwork/Spoon.png");

	std::vector<std::string> cycleNames;
	std::vector<int> framesPerCycle;

	cycleNames.push_back("idle");
	framesPerCycle.push_back(1);
	animSprite.setupCycles(cycleNames, framesPerCycle);
	

	animSprite.setScale(sf::Vector2f(10, 10));
	animSprite.setPosition(sf::Vector2f(890, 100));

	//Spoon::cauldronRect = sf::FloatRect(cauldronRect.left + 5, cauldronRect.top + 5, 
	//					cauldronRect.width - 5, cauldronRect.height - 5);

	Spoon::cauldronRect = cauldronRect;
	setPosition(sf::Vector2f(100, 100));

	currentAngle = 0;
	stirCount = 0;
	prevPoint = animSprite.getPosition();

	//Calculate center of Cauldron
	cauldronCenter.x = cauldronRect.left + cauldronRect.width / 2;
	cauldronCenter.y = cauldronRect.top + cauldronRect.height / 2;
}

void Spoon::update()
{
	/**if (!rect->intersects(cauldronRect))
	{
		return;
		//Need to stay in bounds of cauldron

		auto size = animSprite.getSprite().getTexture()->getSize();
		size.x *= animSprite.getSprite().getScale().x;
		size.y *= animSprite.getSprite().getScale().y;

		//Right: works
		if (animSprite.getPosition().x + size.x > cauldronRect.left + cauldronRect.width)
			animSprite.setPosition(sf::Vector2f(cauldronRect.left + cauldronRect.width, animSprite.getPosition().y));
		
		//Left
		else if (animSprite.getPosition().x < cauldronRect.left)
			animSprite.setPosition(sf::Vector2f(cauldronRect.left, animSprite.getPosition().y));

		//Bottom
		if (animSprite.getPosition().y + size.y + 100 > cauldronRect.top + cauldronRect.height)
			animSprite.setPosition(sf::Vector2f(animSprite.getPosition().x, cauldronRect.top + cauldronRect.height));
		
		//Top
		else if (animSprite.getPosition().y < cauldronRect.top)
			animSprite.setPosition(sf::Vector2f(animSprite.getPosition().x, cauldronRect.top));
	}**/

	if (rect->intersects(cauldronRect))
	{
		sf::Vector2f prevVector = prevPoint - cauldronCenter;
		sf::Vector2f currVector = animSprite.getPosition() - cauldronCenter;

		float numerator = prevVector.x * currVector.x + prevVector.y * currVector.y;
		float denominator = sqrtf(prevVector.x * prevVector.x + prevVector.y * prevVector.y) *
		sqrtf(currVector.x * currVector.x + currVector.y * currVector.y);

		//std::cout << numerator << " / " << denominator << std::endl;
		float num = std::min(numerator / denominator, 1.0f);
		float deltaAngle = (float)acos(num);
		currentAngle += deltaAngle;
		//std::cout << currentAngle << std::endl << std::endl;

		if (currentAngle >= /**1.5 * M_PI**/ getStirValue())
		{
			stirCount++;
			currentAngle = 0;
			//std::cout << "Stirs: " << stirCount << std::endl;
		}
		//std::cout << currentAngle << std::endl;
	}

	prevPoint = animSprite.getPosition();
}

void Spoon::resetStirCount()
{
	currentAngle = 0;
	stirCount = 0;
}
