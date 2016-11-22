// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "prop_movelinear.generated.h"


UCLASS()
class CODEDEMO2_API Aprop_movelinear : public AActor
{
	GENERATED_BODY()
	
public:	
	float runningTime;
	float currentPos;
	bool bIsPaused = false;

	//the actual world position of the end position
		FVector WorldEndPosition;

	// Sets default values for this actor's properties
	Aprop_movelinear();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Pauses the current movement
	virtual void Pause();

	// Unpauses the current movement
	virtual void UnPause();

	//checks the door's current position, handles boolean values, and calls the implementable events
	virtual void CheckStatus();

	// Toggles the door's opened/closed state
	UFUNCTION(BlueprintCallable, Category = "Prop_Movelinear")
		virtual void Toggle();


	// Sets the entity's location between StartPosition and EndPosition, when given a lerp
	// value between 0 and 1
	UFUNCTION(BlueprintCallable, Category = "Prop_Movelinear")
		virtual void SetPosition(float newPos);


	UFUNCTION(BlueprintCallable, Category = "Prop_Movelinear")
		virtual float GetPosition();

	UFUNCTION(BlueprintCallable, Category = "Prop_Movelinear")
		virtual void Open();

	UFUNCTION(BlueprintCallable, Category = "Prop_Movelinear")
		virtual void Close();

	//implementable events
	UFUNCTION(BlueprintImplementableEvent, Category = "Prop_Movelinear")
		void OnOpened();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Prop_Movelinear")
		void OnFullyOpened();

	UFUNCTION(BlueprintImplementableEvent, Category = "Prop_Movelinear")
		void OnClosed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Prop_Movelinear")
		void OnFullyClosed();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop_Movelinear")
		float lerpSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop_Movelinear")
		bool bLoop = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Prop_Movelinear")
		FVector StartPosition;

	//the vector offset from the starting position to move to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop_Movelinear")
		FVector EndPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop_Movelinear")
		bool bStartPaused = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsOpen;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsClosed;

	UFUNCTION(BlueprintCallable, Category = "Prop_Movelinear")
		virtual void IAmHere();
};
