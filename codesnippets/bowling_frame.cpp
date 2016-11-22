// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "bowling_frame.h"

bowling_frame::bowling_frame()
{
	ResetFrame();
	isLast = false;
}

bowling_frame::~bowling_frame()
{
}

void bowling_frame::ResetFrame()
{
	firstThrow			= NOT_THROWN;
	secondThrow			= NOT_THROWN;

	nativeScore			= NOT_THROWN;
	absoluteNativeScore = NOT_THROWN;
	absoluteScore		= NOT_THROWN;

	scoreIsPending = true;

	wasStrike = false;
	wasSpare = false;
}

//given an amount of fallen pins, sets the score for the current throw. Calculates strike/spare booleans. Also sets the nativeScore
//and defaults the absoluteNativeScore to the nativeScore
void bowling_frame::Throw(int amount)
{
	if (firstThrow == NOT_THROWN) //our first throw
	{
		nativeScore = amount;
		firstThrow = amount;
		if (amount == 10) //Strike!
			wasStrike = true;
	}	
	else	//our second throw
	{
		nativeScore += amount;
		secondThrow = amount;
		if (firstThrow + secondThrow == 10) //Spare!
			wasSpare = true;
	}
	absoluteNativeScore = nativeScore;
}

//Given a throw number, returns the score of that throw
int bowling_frame::GetThrowScore(int throwNumber)
{
	throwNumber = FMath::Clamp(throwNumber, 1, 2);
	if (throwNumber == 1)
		return firstThrow;
	else
		return secondThrow;
}

//returns the native score of the frame, excluding strike / spare bonus. Returns NOT_THROWN if no throws have been made.
int bowling_frame::GetNativeScore()
{
	return nativeScore;
}

//Gsets the absolute native score of the frame. overrideType defaults to NULL
int bowling_frame::GsetAbsoluteNativeScore(int override, int overrideType)
{
	//use pointer to make copy-pasting of this snippet easier
	int* p = &absoluteNativeScore;

	if (overrideType == OVERRIDE_TYPE_NULL)
		return *p;

	if (overrideType == OVERRIDE_TYPE_SET)
		*p = override;
	
	if (overrideType == OVERRIDE_TYPE_ADD)
		*p += override;
	
	if (overrideType == OVERRIDE_TYPE_SUBTRACT)
		*p -= override;
	
	if (overrideType == OVERRIDE_TYPE_MULTIPLY)
		*p *= override;

	return *p;
	
}

int bowling_frame::GsetAbsoluteScore(int override, int overrideType)
{
	//use pointer to make copy-pasting of this snippet easier
	int* p = &absoluteScore;

	if (overrideType == OVERRIDE_TYPE_NULL)
		return *p; //just return it immediately to better performance

	if (overrideType == OVERRIDE_TYPE_SET)
		*p = override;

	if (overrideType == OVERRIDE_TYPE_ADD)
		*p += override;

	if (overrideType == OVERRIDE_TYPE_SUBTRACT)
		*p -= override;

	if (overrideType == OVERRIDE_TYPE_MULTIPLY)
		*p *= override;

	return *p;

}