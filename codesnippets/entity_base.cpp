// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "entity_base.h"
#include "entity_registrar.h"


// Sets default values
Aentity_base::Aentity_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	entity_registrar::AddEntity(this);

};

~Aentity_base::Aentity_base()
{
	OnDestroyed();
	entity_registrar::RemoveEntity(this);
};

// Called when the game starts or when spawned
void Aentity_base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aentity_base::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

