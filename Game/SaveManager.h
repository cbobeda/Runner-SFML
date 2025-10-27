#pragma once

#include <iostream>
#include<fstream>
#include<string>

class SaveManager
{
	public:
		SaveManager();
		int getSavedCoins();
		void savecoins(int coins);
	private:
		std::unique_ptr<std::fstream> saveFile;
};

