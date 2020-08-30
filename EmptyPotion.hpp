#include "GrabbableObject.hpp"

class EmptyPotion : public GrabbableObject
{
	public:
		EmptyPotion();
		void update() override {}
};