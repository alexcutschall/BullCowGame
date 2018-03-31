#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp
#include <string>

using FString = std::string;
using int32 = int;

#include <stdio.h>
#include <string>

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
};

class FBullCowGame {
public:
    FBullCowGame(); //constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    bool IsGameWon() const;
    int32 GetHiddenWordLength() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    FBullCowCount SubmittValidGuess(FString Guess);
    
private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

#endif /* FBullCowGame_hpp */
