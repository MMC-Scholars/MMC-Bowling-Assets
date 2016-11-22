// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "entity_registrar.h"
#include "entity_base.generated.h"

UCLASS()
class CODEDEMO2_API Aentity_base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aentity_base();
	~Aentity_base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "entity_base")
		void OnDestroyed();
	
};
