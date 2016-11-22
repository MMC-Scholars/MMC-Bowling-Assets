// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "prop_movelinear.h"


// Sets default values
Aprop_movelinear::Aprop_movelinear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EndPosition = EndPosition.ZeroVector;
	runningTime = 0.0f;
	currentPos = 0.0f;
	bIsClosed = true;
	bIsOpen = false;
}

// Called when the game starts or when spawned
void Aprop_movelinear::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
	runningTime = 0.0f;
	currentPos = 0.0f;

	//gets the world position of the end position
	WorldEndPosition = StartPosition + EndPosition;

	if (bStartPaused) {
		bIsPaused = true;
	}
	else {
		bIsPaused = false;
	}
}

// Called every frame
void Aprop_movelinear::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	IAmHere();

	//if (!bIsPaused || bLoop) {

	currentPos += lerpSpeed * DeltaTime;
	SetPosition(currentPos);
	runningTime += DeltaTime;
	//}

	CheckStatus();

}

void Aprop_movelinear::IAmHere() {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I am ticking!"));
}


//checks the door's current position, handles boolean values, and calls the implementable events
void Aprop_movelinear::CheckStatus()
{
	
	if (GetActorLocation().Equals(StartPosition) && bIsOpen) //door was open but just closed 
	{
		bIsOpen = false;
		bIsClosed = true;
		lerpSpeed = -lerpSpeed; //change the movement direction
		OnFullyClosed();
		Pause();
		if (bLoop) //if we're looping, then reopen/close the door
			Toggle();
	}

	else if (GetActorLocation().Equals(EndPosition) && bIsClosed) //door was closed but just fully opened
	{
		bIsOpen = true;
		bIsClosed = false;
		lerpSpeed = -lerpSpeed;
		OnFullyOpened();
		Pause();
		if (bLoop)
			Toggle();
	}
}

//These functions pause/unpause the movement
void Aprop_movelinear::Pause()
{
	bIsPaused = true;
}

void Aprop_movelinear::UnPause()
{
	bIsPaused = false;
}

//Toggles the door's open/closed state
void Aprop_movelinear::Toggle()
{
	if (bIsOpen)
		Close();
	else
		Open();
}

//Open and close - ensures the door will move in the correct direction, then unpauses movement
void Aprop_movelinear::Open()
{
	if (lerpSpeed < 0)			//if in closing direction
		lerpSpeed = -lerpSpeed;	//then put it in opening direction
	if (!bIsOpen) 
	{
		OnOpened(); //only open the door if it's not already open
		UnPause();
	}
}

void Aprop_movelinear::Close()
{
	if (lerpSpeed > 0)			//if in opening direction
		lerpSpeed = -lerpSpeed;	//then put it in closing direction
	if (!bIsClosed)
	{
		OnClosed(); //only close the door if it's not already open
		UnPause();
	}
}

//Given a 0-1 float lerp value, sets the position of the entity
//between starting position and ending position. Handles clamping
//and checks for opened/closed status
void Aprop_movelinear::SetPosition(float newPos) 
{
	newPos = FMath::Clamp(newPos, 0.0f, 1.0f);

	FVector newLocation;
	newLocation.Z = FMath::Lerp(StartPosition.Z, WorldEndPosition.Z, newPos);
	newLocation.X = FMath::Lerp(StartPosition.X, WorldEndPosition.X, newPos);
	newLocation.Y = FMath::Lerp(StartPosition.Y, WorldEndPosition.Y, newPos);

	SetActorLocation(newLocation);

}

//Returns the 0-1 lerp value of the current position
float Aprop_movelinear::GetPosition() {
	return currentPos;
}

//Blueprint implementable events
/**
void Aprop_movelinear::OnOpened() {
}

void Aprop_movelinear::OnFullyOpened() {
}

void Aprop_movelinear::OnClosed() {
}

void Aprop_movelinear::OnFullyClosed() {
}
*/