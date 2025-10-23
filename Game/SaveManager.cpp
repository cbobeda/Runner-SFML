#include "SaveManager.h"


SaveManager::SaveManager()
{
	saveFile = std::make_unique<std::fstream>();
	saveFile->open("save/save.txt");
	if (!saveFile->is_open())
	{
		std::cout << "file doesn't exist ... generating one \n";
		saveFile->open("save/save.txt", std::ios::out);
	}
}

int SaveManager::getSavedCoins()
{
	int res;
	saveFile->seekp(0);
	std::string line; 
	*saveFile >> line;
	res = atoi(line.c_str());
	return res;
}

void SaveManager::savecoins(int coins)
{
	*saveFile << coins;
}