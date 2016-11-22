// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "bowling_pin.generated.h"

UCLASS()
class CODEDEMO2_API Abowling_pin : public AActor
{
	GENERATED_BODY()
	
public:	

	static Abowling_pin * ArrPins[10];
	static int pinIndex;

	bool hasFallen;

	FVector OriginalLocation;
	FRotator OriginalRotation;

	// Sets default values for this actor's properties
	Abowling_pin();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Checks for significant cahnges in rotation or position
	bool CheckForFallen();
	
	//raises and then lowers
	void RaiseAndLower();

	void Lower();
};
