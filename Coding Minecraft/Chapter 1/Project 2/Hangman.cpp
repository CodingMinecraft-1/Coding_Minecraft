#include <iostream>
#include <string>
#include "Hangman.h"

void Hangman::Begin_Game_Loop() 
{
	do {
		std::cout << "Would you like to play hangman? (Y/N) " << std::endl;
		std::cin >> userIn;

		if (userIn.compare("Y") == 0) Begin_Game();
	} while (userIn.compare("Y") == 0);
}

void Hangman::Begin_Game() 
{
	return;
}

int main() 
{
	Hangman* game = new Hangman();
	game->Begin_Game_Loop();
	system("pause");
	return 0;
}