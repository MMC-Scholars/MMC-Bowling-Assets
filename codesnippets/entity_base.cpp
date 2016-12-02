// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "entity_base.h"

//Initialize the entity registrar
//TArray<Aentity_base* const*, FDefaultAllocator> Aentity_base::registrar = TArray<Aentity_base* const*, FDefaultAllocator>();


// Sets default values
Aentity_base::Aentity_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//AddEntity(this);

};

/*
Aentity_base::~Aentity_base()
{
	RemoveEntity(this);
};
*/

// Called when the game starts or when spawned
void Aentity_base::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = this->GetActorLocation();
	OriginalRotation = this->GetActorRotation();
	health = initialHealth;
	deathTime = 0;
	CalculateHealth(0); //check if we're dead at the start
}

// Called every frame
void Aentity_base::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (isDead && destroyOnDeath)
	{
		deathTime += DeltaTime;
		if (deathTime > deathDelay)
		{
			PrimaryActorTick.bCanEverTick = true;
			Destroy();
		}
	}
}



//Returns reference to the base entity with the given tag
/*Aentity_base* const* Aentity_base::FindEntityByTag(FName tag)
{
	for (int i = 0; i < registrar.Num(); i++)
	{
		if (registrar[i] && (registrar[i])->ActorHasTag(tag))
			return registrar[i];
	}
	return registrar[0];
}
*/
//adds an entity to the registrar
/*
void Aentity_base::AddEntity(Aentity_base* const* newEntity)
{
	registrar.Add(newEntity);
}

//removes an entity from the registrar
void Aentity_base::RemoveEntity(Aentity_base* const* removeEntity)
{
	for (int i = 0; i < registrar.Num(); i++)
	{
		if (registrar.Contains(removeEntity))
			registrar.Remove(removeEntity);
	}
}
*/
void Aentity_base::CalculateHealth(float delta)
{
	//Don't ever process health for objects who start with 0 health
	if (initialHealth == 0)
		return;
	health += delta;

	//Check if we're dead or not
	if (health < 0)
	{
		isDead = true;
		OnKilled();
	}
	else
		isDead = false;

	//Check if we need to start the destroy countdown
	if (isDead && destroyOnDeath)
	{
		PrimaryActorTick.bCanEverTick = true;
	}

}

#if WITH_EDITOR
//Helper function for cleaner updating in the editor
void Aentity_base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	isDead = false;
	initialHealth = 100;

	Super::PostEditChangeProperty(PropertyChangedEvent);

	//Check if we're dead
	CalculateHealth(0);
}
#endif

void Aentity_base::ResetWorldTransform()
{
	SetActorLocation(OriginalLocation);
	SetActorRotation(OriginalRotation);
}
