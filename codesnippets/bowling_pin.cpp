// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "bowling_pin.h"


// Sets default values
Abowling_pin::Abowling_pin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	hasFallen = false;
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

