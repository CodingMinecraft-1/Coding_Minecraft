#include <iostream>
#include <string>
#include "Windows.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Hangman.h"


// This is the function that prints the hangman
void Hangman::Print_Game(bool head, bool body, bool left_arm, bool right_arm, bool left_leg, bool right_leg)
{
	std::cout << "---------------+" << std::endl;
	std::cout << "|              ";
	// It uses a series of if statements to determine which
	// body parts it should print out.
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

// This function resets the available letters
// in case the user starts a new game
void Hangman:: reset_available_letters() {
	char alphabet[26]  = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (int i = 0; i < sizeof(alphabet); i++) {
		available_letters[i] = alphabet[i];
	}
}

// This is where the game loop begins
void Hangman::Begin_Game_Loop() 
{
	// I gather a list of words from a file
	// and store them in an array called words
	std::ifstream infile("words_list.txt");
	std::string line;
	int i = 0;
	while (std::getline(infile, line))
	{
		words[i] = line;
		i++;
	}


	// This is the game loop, it executes until the user
	// asks to be done
	do {
		guesses = 0;
		std::cout << "Would you like to play hangman? (Y/N) " << std::endl;
		std::cin >> userIn;

		// This capitalizes the first letter of the users
		// input
		userIn = toupper(userIn[0]);
		if (userIn.compare("Y") == 0) Begin_Game(); 
	} while (userIn.compare("Y") == 0);
}


// This function checks to see if the user
// has already used the letter they are trying
// to use. If they have not, it removes it
// from the list of available letters by
// changing it to an !
bool Hangman::Check_For_Letter(char letter) {
	for (int i = 0; i < sizeof(available_letters); i++) {
		if (available_letters[i] == letter) {
			available_letters[i] = '!';
			return true;
		}
	}
	return false;
}


// This function is where the game begins
void Hangman::Begin_Game() 
{
	// We reset the available letters in case the user
	// is starting a new game
	reset_available_letters();

	// Pick a random word
	std::string word = words[rand() % 50];
	
	// Declare the output like: _ _ _ _
	// for a word such as farm
	for (int i = 0; i < word.length(); i++) {
		hidden_guess[i] = '_';
	}


	// Print the appropriate screen
	do {
		// This clears the screen so that it seems as if
		// the computer is 'drawing' to the screen
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

		// This prints out the users available letters, if
		// it is an ! then it is not available
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


		// Print out the underscores _ _ _ _
		for (int i = 0; i < word.length(); i++) {
			std::cout << hidden_guess[i] << " ";
		}
		std::cout << std::endl;

		std::cin >> userIn;


		// Give the user a hint if they want, but
		// take a guess away
		if (userIn.compare("hint") == 0) {
			for (int i = 0; i < word.length(); i++) {
				if (hidden_guess[i] == '_') {
					hidden_guess[i] = word[i];
					guesses++;
					break;
				}
			}
		} // Make sure the user's input is not more than one character
		else if (userIn.length() > 0 && userIn.length() < 2) {
			userIn = toupper(userIn[0]);
			if (Check_For_Letter(userIn[0])) {
				bool was_in_word = false;

				// Check to see if the guessed letter was in 
				// the random word, if not take away a life.
				// If it is make sure the output reflects that
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

		// The player has lost break the game loop
		if (guesses == 6) {
			player_guess = word;
			break;
		}
		player_guess = hidden_guess;
	} while(player_guess.compare(word) != 0);

	// Check if the player won and output the appropriate text
	// If they lost show them what the word was.
	system("cls");
	if (guesses != 6) 
		std::cout << "Great job! You guessed the word: " << word << std::endl;
	else 
		std::cout << "Too bad! The word was: " << word << std::endl;

	// Reset the game variables
	guesses = 0;
	userIn = "Y";
	reset_available_letters();
}

int main() 
{
	// Initialize the random seed with the current time
	srand(time(NULL));

	// Create an instance of our game
	Hangman* game = new Hangman();

	// Begin the game loop
	game->Begin_Game_Loop();
	system("pause");
	return 0;
}