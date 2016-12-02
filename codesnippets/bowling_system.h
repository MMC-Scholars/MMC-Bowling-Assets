// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "bowling_pin.h"
#include "bowling_frame.h"
#include "bowling_shared.h"
#include "bowling_system.generated.h"

//enumerator for the score type, for getting the different type of scores
UENUM(BlueprintType)
enum ScoreType
{
	FirstThrow			UMETA(DisplayName="FirstThrow"),
	SecondThrow			UMETA(DisplayName="SecondThrow"),
	NativeScore			UMETA(DisplayName="NativeScore"), 
	AbsoluteNativeScore	UMETA(DisplayName="AbsoluteNativeScore"), 
	AbsoluteScore		UMETA(DisplayName="AbsoluteScore")
};

//enumerator for the endgame type. This is determined by the scores of the last frames
UENUM(BlueprintType)
enum EndgameType
{
	Undetermined			UMETA(DisplayName = "Undetermined"),
	DefaultEnding			UMETA(DisplayName = "DefaultEnding"),
	SpareEnding			UMETA(DisplayName = "SpareEnding"),
	StrikeEnding	UMETA(DisplayName = "StrikeEnding"),
};

UCLASS()
class CODEDEMO2_API Abowling_system : public AActor
{
	GENERATED_BODY()

private:
	//the number of the frame we're in, starting from 0
	int frameIndex;

	bool gameover;


	
	//we have an array of 12 bowling frames that we'll use to score. The last 2 are only used if possible
	TArray<bowling_frame, FDefaultAllocator> Frames;

	//we can't define references to uninitialized frames
	//bowling_frame& lastFrame		= Frames[Frames.size() - 1];
	//bowling_frame& scdLastFrame		= Frames[Frames.size() - 2];
	//bowling_frame& lastNormalFrame	= Frames[Frames.size() - 3];

	// Called on BeginPlay();, assigns pins whose names are given to our array of pins
	//void AssignPins(); //we'll do these in CalculateScore() instead

	//checks the last frames to determine the current endgame type
	void CalculateEndgameType();

	//Checks the last frames to determine if the game is over
	bool CheckForGameover();

	//calculates all of the absolute scores and absolute native scores for the frames
	void ReCalculateAbsoluteScores();
	
public:	
	// Sets default values for this actor's properties
	Abowling_system();

	EndgameType endgameType;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "bowling_system")
		int strikeCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "bowling_system")
		bool printThrowsToScreen;

	//Counts the fallen bowling pins, and calculates the score for the current frame.
	//handles the strike count and strike/spare bonuses
	UFUNCTION(BlueprintCallable, Category = "bowling_system")
		void CalculateScore();

	//Given a frame number and a score type, returns the desired integer score
	UFUNCTION(BlueprintCallable, Category = "bowling_system")
		int GetScoreOfFrame(int frameNumber, ScoreType type);

	//Given a frame number and a score type, returns a string representation of the score
	UFUNCTION(BlueprintCallable, Category = "bowling_system")
		FString GetStringScoreOfFrame(int frameNumber, ScoreType type);

	//Resets all the scores of the game
	UFUNCTION(BlueprintCallable, Category = "bowling_system")
		void ResetGame();

	//Returns the total score for the game, i.e. the absolute score of the current frame.
	UFUNCTION(BlueprintCallable, Category = "bowling_system")
		int GetAbsoluteScore();

	//Gsets the enumerator EndGameType, either DefaultEnding, SpareEnding or StrikeEnding. If it hasn't been determined yet, returns Undetermined.
	//UFUNCTION(BlueprintCallable, Category = "bowling_system")
		EndgameType GsetEndgameType(EndgameType override = Undetermined, const int32 overrideType = OVERRIDE_TYPE_NULL);

	//Returns the number of the current frame, 1-12
	UFUNCTION(BlueprintCallable, Category = "bowling_system")
		int GetNumberOfCurrentFrame();

	UFUNCTION(BlueprintImplementableEvent, Category = "bowling_system")
		void OnStrike();

	UFUNCTION(BlueprintImplementableEvent, Category = "bowling_system")
		void OnSpare();

	UFUNCTION(BlueprintImplementableEvent, Category = "bowling_system")
		void OnGameover();

	
	
};
