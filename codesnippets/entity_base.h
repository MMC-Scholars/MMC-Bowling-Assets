// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "entity_base.generated.h"

UCLASS()
class CODEDEMO2_API Aentity_base : public AActor
{
	GENERATED_BODY()
	
public:	
	//registar of all class instances
	//static TArray<Aentity_base* const*, FDefaultAllocator> registrar;

	//Initial world transform of the entity - set in OnBeginPlay()
	FVector OriginalLocation;
	FRotator OriginalRotation;

	// Sets default values for this actor's properties
	Aentity_base();
	//~Aentity_base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Initial Health Property
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "entity_base")
		float initialHealth = 100;

	//Health Property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		float health = 100;

	//isDead Property
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "entity_base")
		bool isDead = false;

	//Boolean for whether or not we should destroy the actor 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "entity_base")
		bool destroyOnDeath = false;

	//Float for time delay before destroying after death
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "entity_base")
		float deathDelay = 0;
	
	//Running clock for checking if we need to destroy this entity
	float deathTime = 0;

	//Function for modifying health
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		virtual void CalculateHealth(float delta);


	//Step 6: Editor code to make updating values in the editor cleaner
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintImplementableEvent, Category = "entity_base")
		void OnKilled();

	
	
	//Resets the object to its starting location and starting rotation
	UFUNCTION(BlueprintCallable, Category = "entity_base")
		void ResetWorldTransform();


/*
	UFUNCTION(BlueprintCallable, Category = "entity_registrar")
		static Aentity_base* const* FindEntityByTag(FName tag);

	//adds an entity to the registrar
	static void AddEntity(Aentity_base* const* newEntity);

	//removes an entity from the registrar
	static void RemoveEntity(Aentity_base* const* removeEntity);*/
	
};
