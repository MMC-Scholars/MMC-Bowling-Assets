// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "entity_base.h"
#include "bowling_pin.generated.h"

UCLASS()
class CODEDEMO2_API Abowling_pin : public Aentity_base
{
	GENERATED_BODY()
	
public:	

	bool didFall;
	bool isRaisingAndLowering;
	bool isLowering;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "bowling_pin")
		bool isInGame = false;

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
