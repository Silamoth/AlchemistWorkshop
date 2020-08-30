#ifndef ShopManagerHeader
#define ShopManagerHeader

#include <iostream>
#include <vector>
#include <fstream>
#include "Potion.hpp"

class ShopManager
{
	private:
		std::map<std::string, int> potionDemand;	//Maps potion name to demand
		//Demand is measured in how many of that potion people want in a day

	public:
		ShopManager();
		int updateEndOfDay(std::vector<Potion> potionsForSale);
};

#endif
