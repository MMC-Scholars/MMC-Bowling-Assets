// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "bowling_system.h"


Abowling_system::Abowling_system()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//initialize frames
	for (int i = 0; i < Frames.size(); i++)
		Frames[i] = new bowling_frame();

	// Make the last frame know that it's the last one
	lastFrame.isLast = true;


}

// Called when the game starts or when spawned
void Abowling_system::BeginPlay()
{
	Super::BeginPlay();

	AssignPins();

	ResetGame();
}

// Called every frame
void Abowling_system::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called on BeginPlay();, assigns pins whose names are given to our array of pins
void AssignPins();

//checks the last frames to determine the current endgame type
void Abowling_system::CalculateEndgameType()
{
	bowling_frame& lastNormalFrame	= Frames[Frames.size() - 3];
	if (frameIndex <= Frames.size() - 3) //we're in the ninth frame or before
	{
		endgameType = Undetermined;
		return;
	}
	if (frameIndex == Frames.size() - 2) //we're in the last normal frame
	{
		if (lastNormalFrame.wasSpare) //if it was a spare
		{
			endgameType = SpareEnding;
			return;
		}
		else if (lastNormalFrame.wasStrike) //if it was a strike
		{
			endgameType = StrikeEnding;
			return;
		}
		else if (lastNormalFrame.GetThrowScore(2) != NOT_THROWN) //if it was neither a strike nor spare
		{
			endgameType = DefaultEnding;
			return;
		}
	}

}

//Checks the last frames to determine if the game is over
bool Abowling_system::CheckForGameover()
{
	bowling_frame& lastFrame		= Frames[Frames.size() - 1];
	bowling_frame& scdLastFrame		= Frames[Frames.size() - 2];

	if (
		curFrame.isLast
		|| (GsetEndgameType() == DefaultEnding)
		|| (GsetEndgameType() == SpareEnding && scdLastFrame.GetThrowScore(1) != NOT_THROWN)
		|| (GsetEndgameType() == StrikeEnding && (lastFrame.GetThrowScore(1) != NOT_THROWN || scdLastFrame.GetThrowScore(2) != NOT_THROWN))
		)
	{
		gameover = true;
		OnGameover();
	}

	return gameover;
}

//calculates all of the absolute scores and absolute native scores for the frames, also handles bScoreIsPending for each frame
void Abowling_system::ReCalculateAbsoluteScores()
{
	//first SET all the absoluteNativeScores to their native scores
	for (int i = 0; i < Frames.size(); i++)
	{
		Frames[i].GsetAbsoluteNativeScore(Frames[i].GetNativeScore(), OVERRIDE_TYPE_SET);
	}

	//then add strike/spare bonuses to absolute native scores, handling the first 10 frames normally and then handling last 2 specially.
	//also toggles scoreIsPending for all applicable frames
	for (int i = 0; i < Frames.size()-2 ; i++)
	{
		int bonusAmount = 0;
		if (Frames[i].wasStrike && Frames[i + 1].GetThrowScore(1) != NOT_THROWN) //handle strike
		{
			bonusAmount += Frames[i + 1].GetThrowScore(1); //add first throw of next frame...
			if (Frames[i + 1].wasStrike && Frames[i + 2].GetThrowScore(1) != NOT_THROWN) //then add the next throw, of either the second next frame...
			{
				bonusAmount += Frames[i + 2].GetThrowScore(1);
				Frames[i].scoreIsPending = false;
			}
				
			else if (Frames[i + 1].GetThrowScore(2) != NOT_THROWN) //...or the second throw of the first next frame
			{
				bonusAmount += Frames[i + 1].GetThrowScore(2);
				Frames[i].scoreIsPending = false;
			}
				
		}
		else if (Frames[i].wasSpare && Frames[i+1].GetThrowScore(1) != NOT_THROWN) //handle spare
		{
			bonusAmount += Frames[i + 1].GetThrowScore(1);
			Frames[i].scoreIsPending = false;
		}
		else if (!Frames[i].wasSpare && !Frames[i].wasStrike && Frames[i].GetThrowScore(2) != NOT_THROWN) //handle score is pending for closed frames
		{
			Frames[i].scoreIsPending = false;
		}
		//then add the bonus amount
		Frames[i].GsetAbsoluteNativeScore(bonusAmount, OVERRIDE_TYPE_ADD);
	}

	bowling_frame& lastFrame		= Frames[Frames.size() - 1];
	bowling_frame& scdLastFrame		= Frames[Frames.size() - 2];

	//handle last two frames seperately
	{
		int bonusAmount = 0;
		if (scdLastFrame.wasStrike && lastFrame.GetThrowScore(1) != NOT_THROWN)
		{
			bonusAmount += lastFrame.GetThrowScore(1);
			scdLastFrame.scoreIsPending = false;
			lastFrame.scoreIsPending = false; //Could put this in seperate if statement, but this works too.
		}
		scdLastFrame.GsetAbsoluteNativeScore(bonusAmount, OVERRIDE_TYPE_ADD);
		
		//the last frame's absoluteNativeScore is always just its native score, and we already set that
	}
	
	//then finally calculate the running count and absolute scores 
	int runningScore = 0;
	for (int i = 0; i < Frames.size(); i++)
	{
		if (!Frames[i].scoreIsPending)
		{
			runningScore += Frames[i].GsetAbsoluteNativeScore();
			Frames[i].GsetAbsoluteScore(runningScore, OVERRIDE_TYPE_SET);
		}
	}

}

//Counts the fallen bowling pins, and calculates the score for the current frame.
//calls for the handling of the strike count and strike/spare bonuses
void Abowling_system::CalculateScore()
{
	//never calculate anything if the game is already over
	if (gameover)
		return;
	//find the number of pins that have fallen
	int pinCount = 0;
	for (int i = 0; i < ArrPins.size(); i++)
		if (ArrPins[i].CheckForFallen())
			pinCount++;

	//increment the strike count, and call OnStrike()
	{
		if (pinCount == 10)
		{
			strikeCount++;
			OnStrike();
		}
		else
			strikeCount = 0;
	}

	//throw the number of fallen pins to the current frame
	bowling_frame& curFrame = Frames[frameIndex];
	curFrame.Throw(pinCount);

	//Check if we need to call OnSpare
	if (curFrame.wasSpare)
		OnSpare();

	//calculate the endgame type
	CalculateEndgameType();

	//check if the game is over
	CheckForGameover();

	//increment the frame index if we need to
	if ((!gameover) && (curFrame.wasStrike || curFrame.GetThrowScore(2) != NOT_THROWN))
		frameIndex++;

	//Re-calculate the absolute scores for each frame
	ReCalculateAbsoluteScores();
}

//Given a frame number and a score type, returns the desired score
int Abowling_system::GetScoreOfFrame(int frameNumber, ScoreType type)
{
	//we'll let blueprinters start from 1
	frameNumber--;

	if (type == FirstThrow)
		return Frames[frameNumber].GetThrowScore(1);
	if (type == SecondThrow)
		return Frames[frameNumber].GetThrowScore(2);
	if (type == NativeScore)
		return Frames[frameNumber].GetNativeScore();
	if (type == AbsoluteNativeScore)
		return Frames[frameNumber].GsetAbsoluteNativeScore();
	if (type == AbsoluteScore)
		return Frames[frameNumber].GsetAbsoluteScore();

	return NOT_THROWN;
}

//Given a frame number and a score type, returns a string representation of the score
FString Abowling_system::GetStringScoreOfFrame(int frameNumber, ScoreType type)
{
	int iScore = GetScoreOfFrame(frameNumber, type);

	FString sScore;

	if (iScore == NOT_THROWN || Frames[frameNumber].scoreIsPending)
		sScore = FString(TEXT(" "));

	else if (Frames[frameNumber].wasSpare && type = SecondThrow)
		sScore = FString(TEXT("/"));
	else if (Frames[frameNumber].wasStrike && type = SecondThrow)
		sScore = FString(TEXT("X"));
	else if (iScore == 0 && type = AbsoluteScore)
		sScore = FString(TEXT("--"));
	else if (iScore == 0)
		sScore = FString(TEXT("-"));
	else
		sScore = FString::FromInt(iScore);

	return sScore;
}

//Resets all the scores of the game
void Abowling_system::ResetGame()
{
	strikeCount = 0;
	frameIndex = 0;
	gameover = false;

	endgameType = Undetermined;

	//reset all frames
	for (int i = 0; i < Frames.size(); i++)
	{
		Frames[i].ResetFrame();
	}
}

//Returns the total score for the game, i.e. the absolute score of the current frame.
int Abowling_system::GetAbsoluteScore()
{
	return Frames[frameIndex].GsetAbsoluteScore();
}

//Gsets the enumerator EndGameType, either DefaultEnding, SpareEnding or StrikeEnding. If it hasn't been determined yet, returns Undetermined.
EndgameType Abowling_system::GsetEndgameType(EndgameType override, const int32 overrideType)
{
	if (overrideType == OVERRIDE_TYPE_SET)
		endgameType = override;
	return endgameType;
}

//Returns the number of the current frame, 1-11
int Abowling_system::GetNumberOfCurrentFrame()
{
	return frameIndex - 1;
}
