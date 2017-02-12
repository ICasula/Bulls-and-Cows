/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

FText Guess = "";
bool PlayAgain = false;

FBullCowGame BCGame;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess();
bool AskToPlayAgain();
void PrintGameSummary();

int main()
{
	do {
		PrintIntro();
		PlayGame();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);

	return 0;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	while (BCGame.GetCurrentTry() <= MaxTries && !BCGame.IsGameWon()) {
		Guess = GetValidGuess(); 

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}

	PrintGameSummary();
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		//get a guess from the player
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeated letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n";
			break;
		default:
			break;
		}

	} while (Status != EGuessStatus::OK);
	return Guess;

}

void PrintIntro()
{
	//introduce the game
	std::cout << "Welcome to Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nCongrats, you won!\n\n";
	}
	else
	{
		std::cout << "\nBad luck, better luck next time!\n\n";
	}
}