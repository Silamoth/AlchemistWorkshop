#include "Hand.hpp"

Hand::Hand()
{	
	std::vector<std::string> cycleNames;
	std::vector<int> framesPerCycle;

	cycleNames.push_back("grab");
	framesPerCycle.push_back(1);
	//animSprite.setupCycles(cycleNames, framesPerCycle);
	animSprite = AnimatedSprite(1, 32, "Artwork/Hand.png", cycleNames, framesPerCycle);

	holdingItem = false;
	canInteract = true;
	interactTimer = 0;

	//heldObject = new GrabbableObject();

	buffer = new sf::SoundBuffer();
	if (!buffer->loadFromFile("Audio/Grab.wav"))
	{
		std::cout << "Audio file failed to load" << std::endl;
		throw -3;
		return;
	}

	grabSound.setBuffer(*buffer);
}

void Hand::update(sf::Time delta, sf::Vector2f mousePos)
{
	animSprite.update(delta);
	animSprite.setPosition(mousePos);

	if (!canInteract)
	{
		interactTimer += delta.asMilliseconds();

		const int pickupTime = 250;

		if (interactTimer >= pickupTime)
		{
			interactTimer = 0;
			canInteract = true;
		}
	}

	if (holdingItem)
		heldObject->setPosition(mousePos);

	//std::cout << holdingItem << std::endl;

	sf::Vector2f size = sf::Vector2f(animSprite.getSprite().getTexture()->getSize());
	size.x *= animSprite.getSprite().getScale().x;
	size.y *= animSprite.getSprite().getScale().y;

	sf::Vector2f position = sf::Vector2f(animSprite.getPosition());
	//position.x *= animSprite.getSprite().getScale().x;
	//position.y *= animSprite.getSprite().getScale().y;

	rect = new sf::FloatRect(position, size);
}

void Hand::setHeldObject(GrabbableObject* newObj)
{
	heldObject = newObj;
	interact();
}

void Hand::removeObject()
{
	holdingItem = false;
	interact();
}

void Hand::interact()
{
	canInteract = false;
	grabSound.play();
}

Hand::~Hand()
{
	//if (heldObject != NULL)
		//delete heldObject;
}
