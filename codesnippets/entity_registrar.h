// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "entity_base.h"

/** Contains and handles the static list of entities
 * 
 */
class CODEDEMO2_API entity_registrar
{
public:

	static TArray<Aentity_base*> registrar;

	entity_registrar();
	~entity_registrar();
	
	//Returns reference to the base entity with the given tag
	UFUNCTION(BlueprintCallable, Category = "entity_registrar")
		static Aentity_base& FindEntityByTag(FText tag);

	//adds an entity to the registrar
	static void AddEntity(Aentity_base& newEntity);

	//removes an entity from the registrar
	static void RemoveEntity(Aentity_base& removeEntity);
};
