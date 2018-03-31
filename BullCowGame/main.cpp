/* This is the console executable. It makes use of the BullCowClass.
 This acts as the view in the MVC pattern, and is responsible for all
 user interaction. For game logic, see the FBullCowGame class.
 */

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

// the entry point for our application
int main()
{
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        PrintGameSummary();
        bPlayAgain = AskToPlayAgain();
       }
    while (bPlayAgain);
    return 0;
}


void PrintIntro()
{
std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
std::cout << std::endl;
std::cout <<"       db        db "<< std::endl;
std::cout <<"      d88          88 "<< std::endl;
std::cout <<"     888            888 "<< std::endl;
std::cout <<"    d88              888b "<< std::endl;
std::cout <<"     888            d88P "<< std::endl;
std::cout <<"     Y888b/``````\\8888 "<< std::endl;
std::cout <<",---- Y888      Y88P`````\\ "<< std::endl;
std::cout <<"|        ,'`\\_/``\\ |,,  | "<< std::endl;
std::cout <<"\\,,,,-| | o | o /  |  ```' "<< std::endl;
std::cout <<"      |  \"\"\" \"\"\"   | "<< std::endl;
std::cout <<"    /              \\ "<< std::endl;
std::cout <<"   |                 \\ "<< std::endl;
std::cout <<"   |  ,,,,----'''``` | "<< std::endl;
std::cout <<"   |``   @    @      | "<< std::endl;
std::cout <<"    \\,,    ___    ,,/ "<< std::endl;
std::cout <<"       \\__|   |__/ " << std::endl;
std::cout <<"          | | | " << std::endl;
std::cout <<"          \\_|_/ " << std::endl;
    std::cout << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm think of?\n";
    std::cout << std::endl;
    return;
}


void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    while ( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) {
        FText Guess = GetValidGuess();
        
        // Submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmittValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    return;
}


FText GetValidGuess()
{
FText Guess = "";
EGuessStatus Status = EGuessStatus::Invalid;

    do{
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your Guess: ";
        std::getline (std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch(Status)
        {
            case (EGuessStatus::Wrong_Length):
                std::cout << "That word is not " << BCGame.GetHiddenWordLength() << " letters!\n\n";
                break;
            case (EGuessStatus::Not_Lowercase):
                std::cout << "All letters must be lowercase!\n\n";
                break;
            case (EGuessStatus::Not_Isogram):
                std::cout << "That's not an Isogram!\n\n";
                break;
            default:
            //assume guess is valid
            break;
        }
    } while (Status != EGuessStatus::OK);
    return Guess;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon() == true){
        std::cout << "YOU WON! CONGRATULATIONS!\n";
    } else {
        std::cout << "Aww, better luck next time.\n";
    }
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? (y/n) ";
    FText Response = "";
    std::getline(std::cin, Response);
    
    std::cout << std::endl;
    return (Response[0] == 'y') || (Response[0] == 'Y');
    
}
