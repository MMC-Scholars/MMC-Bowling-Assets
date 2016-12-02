// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "bowling_pin.h"


// Sets default values
Abowling_pin::Abowling_pin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	didFall = false;
}

// Called when the game starts or when spawned
void Abowling_pin::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void Abowling_pin::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Checks for significant cahnges in rotation or position
bool Abowling_pin::CheckForFallen()
{
	//Never say we just fell if we had already fallen
	if (didFall) //if we're in the first throw of the frame, this is never true as it is set to false in the Abowling_system::CalculateScore()
	{
		return false; //never register as falling twice in a row
	}
		return false;
	if (FMath::Abs(GetActorRotation().Roll - OriginalRotation.Roll) > 10)	
		didFall = true;
	if (FMath::Abs(GetActorRotation().Pitch - OriginalRotation.Pitch) > 10)
		didFall = true;
	didFall = false;
	return didFall;
}

//raises and then lowers the pin in a sine-wave fashion, by enabling the pin's tick
//actual raising and lowering done inside the tick fu
void Abowling_pin::RaiseAndLower(){}


void Abowling_pin::Lower()
{

}

