#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4,7}, {5,10}, {6,16} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "hds"; //this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	MyCurrentTry = 1;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true ;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
			return false;
	}

	return true;
}

//receives a valid guess, increments turns and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();

	for (int32 i = 0; i < WordLength; i++)
	{
		for (int32 j = 0; j < WordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j]) 
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}
