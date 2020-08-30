#ifndef handHeader
#define handHeader

#include <SFML/Audio.hpp>
#include "AnimatedSprite.hpp"
#include "Ingredient.hpp"
#include "GrabbableObject.hpp"

class Hand
{
	private:
		AnimatedSprite animSprite;
		bool holdingItem;
		GrabbableObject* heldObject;

		bool canInteract;
		sf::Int32 interactTimer;

		sf::FloatRect* rect;

		sf::SoundBuffer* buffer;
		sf::Sound grabSound;

	public:
		Hand();
		void update(sf::Time delta, sf::Vector2f mousePos);
		sf::Sprite getSprite() { return animSprite.getSprite(); }
		void setHoldingItem(bool val) { holdingItem = val; }
		bool getHoldingItem() { return holdingItem; }

		GrabbableObject* getHeldObject() { return heldObject; }
		void setHeldObject(GrabbableObject* newIng);

		bool getCanInteract() { return canInteract; }
		void removeObject();
		void interact();

		sf::FloatRect getRect() { return *rect; }

		~Hand();
};

#endif
