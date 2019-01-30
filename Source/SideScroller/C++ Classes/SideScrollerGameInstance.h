// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SideScrollerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER_API USideScrollerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	USideScrollerGameInstance();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasDied;
	
	
};
