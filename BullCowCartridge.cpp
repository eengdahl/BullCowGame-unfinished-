// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    GetValidWords(Words);
    SetupGame();

    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug line 
    PrintLine(TEXT("The nr of possible words is: %i"), Words.Num()); // Debug line
    PrintLine(TEXT("The nr of valid words is: %i"), GetValidWords(Words).Num());   
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }

    else    // Checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to the Bull Cow game!"));

    HiddenWord = TEXT("cakes"); 
    Lives = HiddenWord.Len();
    bGameOver = false;


    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess here and press Enter"));
    PrintLine(TEXT("You have %i lives left"), Lives);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\n\nPress Enter to try again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
 if (Guess == HiddenWord) 
    {
        PrintLine(TEXT("You have Won!!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, Try guessing again!\nYou have %i lives left"), Lives);
        return;
    }

      if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));   
        return;           
    }

     PrintLine(TEXT("Lost a life!"));
     --Lives;

     if (Lives <= 0)
    {
    ClearScreen();
    PrintLine(TEXT("You have no lives left"));
    PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
    EndGame();
    return;
    }

       PrintLine(TEXT("Guess again. You have %i lives left"), Lives);
    
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{  


for (int32 Index = 0; Index < Word.Len(); Index++)
{
    for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
    {
        if (Word[Index] == Word[Comparison])
        {
        return false;
        }
    }
}
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
   TArray<FString> ValidWords;

 for (FString Word : WordList)
    
        if (Word.Len() >=4 && Word.Len() <=8 && IsIsogram(Word))
        {
            if (IsIsogram(Word))
            {
            ValidWords.Emplace(Word);
            }
        }
        return ValidWords;
    
}
