#pragma once
#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame(){
    Reset();
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
    MyCurrentTry = 1;
    return;
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
    
    TMap<int32, int32> WordLengthToMaxTries { {3,5}, {4,5}, {5,8}, {6,10} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    } else if (!IsLowercase(Guess)) {
        return EGuessStatus::Not_Lowercase;
    } else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    } else {
    return EGuessStatus::OK; // make actual error
    }
}

FBullCowCount FBullCowGame::SubmittValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 HiddenWordLength = MyHiddenWord.length();
    
        // compare letters against hidden word
    for(int32 MGChar = 0; MGChar < HiddenWordLength; MGChar++){
        for(int32 HWChar = 0; HWChar < HiddenWordLength; HWChar++) {
            if (Guess[MGChar] == MyHiddenWord[HWChar]){
                if (MGChar == HWChar){ // if they're in the same place
                    BullCowCount.Bulls++; // increment bulls
                }
                else {
                    BullCowCount.Cows++; //increment cows
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == HiddenWordLength) {
        bGameIsWon = true;
    }
    else {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    if (Word.length() <= 1){ return true; }
    
    TMap<char, bool> LetterSeen; //setup our map
    for(auto Letter: Word)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) { return false; }
        else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
    for(auto Letter : Word)
        {
        if (islower(Letter)) { return true; }
        else { return false; }
        }
    return true;
}

