#include <iostream>
#include <string>
#include "Windows.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Hangman.h"

void Hangman::Print_Game(bool head, bool body, bool left_arm, bool right_arm, bool left_leg, bool right_leg)
{
	std::cout << "---------------+" << std::endl;
	std::cout << "|              ";
	if (head)
		std::cout << "0" << std::endl;
	else
		std::cout << std::endl;

	std::cout << "|             ";
	if (left_arm)
		std::cout << "/";
	else
		std::cout << " ";

	if (body)
		std::cout << "|";

	if (right_arm)
		std::cout << "\\" << std::endl;
	else
		std::cout << std::endl;

	std::cout << "|             ";

	if (left_leg)
		std::cout << "/";
	if (right_leg)
		std::cout << " \\";
	std::cout << std::endl;

	std::cout << "|" << std::endl << "|" << std::endl << "|" << std::endl;
	std::cout << "====" << std::endl << std::endl;
}

void Hangman:: reset_available_letters() {
	char alphabet[26]  = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (int i = 0; i < sizeof(alphabet); i++) {
		available_letters[i] = alphabet[i];
	}
}

void Hangman::Begin_Game_Loop() 
{
	std::ifstream infile("words_list.txt");
	std::string line;
	int i = 0;
	while (std::getline(infile, line))
	{
		words[i] = line;
		i++;
	}


	do {
		guesses = 0;
		std::cout << "Would you like to play hangman? (Y/N) " << std::endl;
		std::cin >> userIn;
		if (userIn.compare("Y") == 0) Begin_Game(); 
	} while (userIn.compare("Y") == 0);
}

bool Hangman::Check_For_Letter(char letter) {
	for (int i = 0; i < sizeof(available_letters); i++) {
		if (available_letters[i] == letter) {
			available_letters[i] = '!';
			return true;
		}
	}
	return false;
}

void Hangman::Begin_Game() 
{
	reset_available_letters();
	std::string word = words[rand() % 50];
	std::cout << word << word.length() << std::endl;
	
	for (int i = 0; i < word.length(); i++) {
		hidden_guess[i] = '_';
	}

	do {
		system("cls");
		switch (guesses)
		{
			case 0:
				Print_Game(0, 0, 0, 0, 0, 0);
				break;
			case 1:
				Print_Game(1, 0, 0, 0, 0, 0);
				break;
			case 2:
				Print_Game(1, 1, 0, 0, 0, 0);
				break;
			case 3:
				Print_Game(1, 1, 1, 0, 0, 0);
				break;
			case 4:
				Print_Game(1, 1, 1, 1, 0, 0);
				break;
			case 5:
				Print_Game(1, 1, 1, 1, 1, 0);
				break;
			case 6:
				Print_Game(1, 1, 1, 1, 1, 1);
				break;
		}

		for (int i = 0; i < sizeof(available_letters); i++)
		{
			if(available_letters[i] != '!')
				std::cout << available_letters[i] << " ";
			if (i == sizeof(available_letters) / 2)
			{
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;

		for (int i = 0; i < word.length(); i++) {
			std::cout << hidden_guess[i] << " ";
		}
		std::cout << std::endl;

		std::cin >> userIn;
		if (userIn.length() > 0) {
			userIn = toupper(userIn[0]);
			if (Check_For_Letter(userIn[0])) {
				bool was_in_word = false;

				for (int i = 0; i < word.length(); i++) {
					if (toupper(word[i]) == userIn[0]) {
						hidden_guess[i] = word[i];
						was_in_word = true;
					}
				}

				if (!was_in_word)
					guesses++;
			} 
		}

		if (guesses == 6) {
			player_guess = word;
			break;
		}
		player_guess = hidden_guess;
	} while(player_guess.compare(word) != 0);

	system("cls");
	if (guesses != 6) 
		std::cout << "Great job! You guessed the word: " << word << std::endl;
	else 
		std::cout << "Too bad! The word was: " << word << std::endl;

	guesses = 0;
	userIn = "Y";
	reset_available_letters();
}

int main() 
{
	srand(time(NULL));
	Hangman* game = new Hangman();
	game->Begin_Game_Loop();
	system("pause");
	return 0;
}