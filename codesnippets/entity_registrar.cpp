// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeDemo2.h"
#include "entity_registrar.h"

entity_registrar::entity_registrar()
{
}

entity_registrar::~entity_registrar()
{
}


//Returns reference to the base entity with the given tag
static Aentity_base& FindEntityByTag(FName tag)
{
	for (int i = 0; i < registrar.Num(); i++)
	{
		if (*registrar[i].ActorHasTag(tag))
			return *registrar[i];
	}
}


//adds an entity to the registrar
static void AddEntity(Aentity_base& newEntity)
{
	registrar.Add(&newEntity);
}

//removes an entity from the registrar
static void RemoveEntity(Aentity_base& removeEntity)
{
	for (int i = 0; i < registrar.Num(); i++)
	{
		if (registrar.Contains(&removeEntity))
			registrar.Remove(&removeEntity);
	}
}