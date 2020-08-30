#include "ShopManager.hpp"

ShopManager::ShopManager()
{
	//Initialize potion demands from file

	std::ifstream reader;
	reader.open("Data/potionDemand.txt");

	while (reader.peek() != -1)
	{
		std::string name;
		int demand;
		reader >> name >> demand;

		potionDemand.insert(std::pair<std::string, int>(name, demand));
	}

	reader.close();
}

int ShopManager::updateEndOfDay(std::vector<Potion> potionsForSale)
{
	for (auto it = potionsForSale.begin(); it != potionsForSale.end(); it++)
	{
		
	}
}
