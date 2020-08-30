#include <fstream>
#include "IngredientManager.hpp"
#include "EmptyPotion.hpp"

IngredientManager::IngredientManager()
{
	//Read available ingredients

	std::ifstream reader;
	reader.open("Data/availableIngredients.txt");

	int x = 250;
	int i = 0;

	while (reader.peek() != -1)
	{
		std::string name;
		int r, g, b;
		reader >> name >> r >> g >> b;
		//Ingredient newIng(name, sf::Color(r, g, b));

		availableObjects.push_back(new Ingredient(name, sf::Color(r, g, b)));
		availableObjects[i]->setPosition(sf::Vector2f(x, 1120));
		isObjectActive.push_back(true);

		//newIng.setPosition(sf::Vector2f(x, 1120));
		x += 125;

		i++;
	}

	reader.close();

	availableObjects.push_back(new EmptyPotion());
	availableObjects[i]->setPosition(sf::Vector2f(x, 1120));
	isObjectActive.push_back(true);

	x += 125;
	i++;

	availableObjects.push_back(new EmptyPotion());
	availableObjects[i]->setPosition(sf::Vector2f(x, 1120));

	//Read recipes

	reader.open("Data/recipes.txt");

	while (reader.peek() != -1)
	{
		std::string line;
		reader >> line;
		int equalsIndex = line.find("=");
		std::string leftHand = line.substr(0, equalsIndex);
		std::string rightHand = line.substr(equalsIndex + 1);

		//std::vector<std::string> ingredientNames;
		std::set<std::string> ingredientNames;

		while (leftHand.find("+") != -1)
		{
			int plusIndex = leftHand.find("+");
			std::string ingredientName = leftHand.substr(0, plusIndex);
			leftHand = leftHand.substr(plusIndex + 1);

			ingredientNames.insert(ingredientName);
		}
		ingredientNames.insert(leftHand);

		int semiIndex = rightHand.find(";");
		std::string potionName = rightHand.substr(0, semiIndex);
		std::string colors = rightHand.substr(semiIndex + 1);

		std::vector<int> colorNums;

		const int cauldronNum = 204;

		while (colors.find(",") != -1)
		{
			int commaIndex = colors.find(",");
			std::string color = colors.substr(0, commaIndex);
			colors = colors.substr(commaIndex + 1);

			colorNums.push_back(stoi(color) * 255 / cauldronNum);
		}
		colorNums.push_back(stoi(colors) * 255 / cauldronNum);

		Recipe newRecipe(potionName, ingredientNames, sf::Color(colorNums[0], colorNums[1], colorNums[2]));
		recipes.push_back(newRecipe);

		hasRecipe = false;
	}

	reader.close();

	//Initialize ingredient bar
	ingredientBarTexture = new sf::Texture();
	if (!ingredientBarTexture->loadFromFile("Artwork/IngredientBar.png"))
	{
		throw 2;	//File not loaded
		return;
	}

	ingredientBar.setTexture(*ingredientBarTexture);
	ingredientBar.setScale(2.2, 6);
	ingredientBar.setPosition(100, 1100);

	sf::Vector2f size = sf::Vector2f(ingredientBar.getTexture()->getSize());
	size.x *= ingredientBar.getScale().x;
	size.y *= ingredientBar.getScale().y;

	barRect = new sf::FloatRect(ingredientBar.getPosition(), size);

	hasPotion = false;

	particleEmitter = ParticleEmitter(3, 400);

	//Initialize arrows

	rightArrow = BarArrow(50, sf::Vector2f(ingredientBar.getPosition().x + (ingredientBarTexture->getSize().x - 50) * ingredientBar.getScale().x, ingredientBar.getPosition().y + 15));
	leftArrow = BarArrow(-50, sf::Vector2f(ingredientBar.getPosition().x + 15, ingredientBar.getPosition().y + 15));

	barOffset = 0;
	prevOffset = 0;
}

void IngredientManager::update(Hand* hand, Cauldron* cauldron, Spoon* spoon, sf::Time delta)
{
	//Handle bar offset stuff
	{
		barOffset = leftArrow.update(hand, barOffset);
		barOffset = rightArrow.update(hand, barOffset);

		int diff = barOffset - prevOffset;

		for (int i = 0; i < availableObjects.size(); i++)
		{
			auto object = availableObjects[i];
			availableObjects[i]->setPosition(sf::Vector2f(object->getRect().left + diff, object->getRect().top));
			object = availableObjects[i];

			if (object->getRect().left < leftArrow.getRect().left + leftArrow.getRect().width + 25)
				isObjectActive[i] = false;
			else if (object->getRect().left + object->getRect().width > rightArrow.getRect().left - 25)
				isObjectActive[i] = false;
			else
				isObjectActive[i] = true;
		}

		prevOffset = barOffset;
	}

	//Handle Hand picking up GrabbableObjects from inventory bar
	{
		std::vector<GrabbableObject*> newObjects;
		std::vector<bool> newActive;

		int index = 0;

		for (int i = 0; i < availableObjects.size(); i++)
		{
			bool keep = true;

			if (!hand->getHoldingItem() && hand->getCanInteract() && isObjectActive[i])
			{
				if (hand->getRect().intersects(availableObjects[i]->getRect()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					hand->setHoldingItem(true);
					//Ingredient* newIng = new Ingredient(availableObjects[i]->getName(), availableObjects[i]->getColor());
					//newIng->setPosition(hand->getSprite().getPosition());
					hand->setHeldObject(availableObjects[i]);
					keep = false;
				}
			}

			if (keep)
			{
				newObjects.push_back(availableObjects[i]);
				newActive.push_back(isObjectActive[i]);
			}
		
			index++;
		}

		availableObjects = newObjects;
		isObjectActive = newActive;
	}

	//Handle Hand dropping Ingredients onto IngredientBar
	{
		
		if (hand->getHoldingItem() && hand->getCanInteract() /**&& dynamic_cast<Ingredient*>(hand->getHeldObject()) != NULL**/)
		{
			if (hand->getRect().intersects(*barRect) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				hand->removeObject();
				availableObjects.push_back(hand->getHeldObject());
				isObjectActive.push_back(true);
				hand->setHoldingItem(false);
			}
		}
		//std::cout << hand->getHoldingItem() << std::endl;
	}

	//Handle Hand dropping Ingredients onto Cauldron
	{
		if (hand->getHoldingItem() && hand->getCanInteract() && dynamic_cast<Ingredient*>(hand->getHeldObject()) != NULL)
		{
			if (hand->getRect().intersects(cauldron->getRect()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//cauldron->addIngredient(Ingredient(hand->getHeldObject()->getName(), sf::Color::Blue));
				cauldron->addIngredient(*static_cast<Ingredient*>(hand->getHeldObject()));
				hand->removeObject();
			}
		}
	}

	//Handle Hand picking up Spoon
	{
		if (!hand->getHoldingItem() && hand->getCanInteract())
		{
			if (hand->getRect().intersects(spoon->getRect()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				hand->setHoldingItem(true);
				hand->setHeldObject(spoon);
			}
		}
	}

	//Handle Hand dropping Spoon
	{
		if (hand->getHoldingItem() && hand->getCanInteract() && dynamic_cast<Spoon*>(hand->getHeldObject()) != NULL)
		{
			if (hand->getRect().intersects(spoon->getRect()) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				hand->setHoldingItem(false);
				hand->removeObject();
			}
		}
	}

	//Used for next two sections
	float stirFrac = (float)spoon->getStirCount() + spoon->getCurrentAngle() / spoon->getStirValue();
	float prop = stirFrac / 3.0f;

	//Check if any recipes have been made
	{
		//float stirFrac = (float)spoon->getStirCount() + spoon->getCurrentAngle() / spoon->getStirValue();
		//std::cout << stirFrac << std::endl;
		//float prop = stirFrac / 3.0f;

		if (stirFrac == 0 && !hasPotion)
		{
			//Check if current ingredients can create a recipe

			for (auto it = recipes.begin(); it != recipes.end(); it++)
			{
				if (cauldron->checkRecipe(*it))
				{
					currentRecipe = &(*it);
					hasRecipe = true;
					spoon->resetStirCount();
					cauldronStartingColor = cauldron->getColor();
					//std::cout << (int)cauldronStartingColor.r << std::endl;
					//std::cout << "Changed cauldronStartingColor" << std::endl << std::endl;
				}
			}
		}

		//std::cout << stirFrac << "," << prop << std::endl;

		if (prop > 0 && !hasPotion && hasRecipe)
		{
			sf::Color newColor = cauldronStartingColor;

			float rSlope = ((float)currentRecipe->getColor().r - (float)cauldronStartingColor.r) / 3.0f;
			float gSlope = ((float)currentRecipe->getColor().g - (float)cauldronStartingColor.g) / 3.0f;
			float bSlope = ((float)currentRecipe->getColor().b - (float)cauldronStartingColor.b) / 3.0f;
			
			newColor.r += rSlope * stirFrac;
			newColor.g += gSlope * stirFrac;
			newColor.b += bSlope * stirFrac;
			//std::cout << "rSlope: " << rSlope << std::endl;
			//std::cout << stirFrac << ", " << (int)newColor.r << std::endl << std::endl;
		
			//std::cout << r << ", " << g << ", " << b << std::endl;
			cauldron->setColor(sf::Color(newColor.r, newColor.g, newColor.b));
		}

		if (spoon->getStirCount() >= 3 && hasRecipe)
		{
			//potion = Potion(currentRecipe->getPotionName());
			hasPotion = true;
			spoon->resetStirCount();
			hasRecipe = false;
			//std::cout << "Ready" << std::endl;
		}
	}

	//Handle filling EmptyPotion with contents of Cauldron
	{
		if (hand->getHoldingItem() && hand->getCanInteract() && hasPotion && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (hand->getHeldObject()->getRect().intersects(cauldron->getRect()) && dynamic_cast<EmptyPotion*>(hand->getHeldObject()) != NULL)
			{
				hand->setHeldObject(new Potion(currentRecipe->getPotionName()));
				hasPotion = false;
				cauldron->clearIngredients();
				cauldron->setColor(cauldronStartingColor);
				spoon->resetStirCount();
			}
		}
	}

	//Handle particles in and around Cauldron
	{
		if (hasPotion || (hasRecipe && prop > 0))
		{
			if (rand() % 400 == 0)
			{
				sf::Vector2f spawnPosition = sf::Vector2f(cauldron->getRect().left, cauldron->getRect().top);
				spawnPosition.x += rand() % (int)(cauldron->getRect().width);
				spawnPosition.y += rand() % (int)(cauldron->getRect().height);

				//Modify color of particle based on current Cauldron color

				sf::Color particleColor = cauldron->getColor();
				particleColor.r += 20;
				particleColor.g += 20;
				particleColor.b += 20;

				particleEmitter.randomizeParticles(spawnPosition, particleColor);
				particleEmitter.emitParticles();
				//std::cout << "Emitted particles" << std::endl;
			}
		}
	}

	particleEmitter.update(delta);
}

std::vector<sf::Sprite> IngredientManager::getObjects()
{
	std::vector<sf::Sprite> sprites;

	for (int i = 0; i < availableObjects.size(); i++)
	{
		if (isObjectActive[i])
			sprites.push_back(availableObjects[i]->getSprite());
	}

	for (int i = 0; i < particleEmitter.getParticleSprites().size(); i++)
		sprites.push_back(particleEmitter.getParticleSprites()[i]);

	sprites.push_back(leftArrow.getSprite());
	sprites.push_back(rightArrow.getSprite());

	return sprites;
}
