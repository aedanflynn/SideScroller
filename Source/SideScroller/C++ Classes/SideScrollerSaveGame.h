// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SideScrollerSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API USideScrollerSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	USideScrollerSaveGame();

public:

	UPROPERTY()
		int32 PawnScoreInstance;

	UPROPERTY()
		FString PlayerSaveSlotName;

	UPROPERTY()
		uint32 UserIndex;

	UPROPERTY()
		FDateTime PlayerSaveSlotDate;

	UPROPERTY()
		TArray<FString> Inventory;

	
	
};
