#pragma once

class Hangman {

public:
	void Begin_Game_Loop();

	void Begin_Game();

	void Print_Game(bool head, bool body, bool left_arm, bool right_arm, bool left_leg, bool right_leg);

	bool Check_For_Letter(char letter);

	void reset_available_letters();

	char hidden_guess[100];

	std::string userIn;

	std::string words[49];

	char available_letters[26];

	std::string player_guess = "";

	int guesses;

};