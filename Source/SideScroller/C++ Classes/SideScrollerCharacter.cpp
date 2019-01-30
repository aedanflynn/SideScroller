// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerCharacter.h"
#include "SideScroller.h"
#include "SideScrollerGameInstance.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

const FName ASideScrollerCharacter::PlayerTagName(TEXT("Player"));


// Sets default values
ASideScrollerCharacter::ASideScrollerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterStats.health = 1.f;
	CharacterStats.score = 0;
	canSaveGame = false;
	hasCompletedCustomSaveGame = false;
	isAssemblingSaveGameData = false;
	hasCompletedLoadGame = false;

	this->Tags.Add(PlayerTagName);

}

// Called when the game starts or when spawned
void ASideScrollerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASideScrollerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SaveGameLogic();
	LoadGameLogic();
}

// Called to bind functionality to input
void ASideScrollerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma region Save/Load Logic
void ASideScrollerCharacter::SaveGameLogic()
{
	if (canSaveGame)
	{
		InitSaveGame();
		canSaveGame = false;
	}
	else
	{
		if (!isAssemblingSaveGameData) 
		{
			if (this->IsValidLowLevel())
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString(TEXT("Getting ready to save...")), true);
				isAssemblingSaveGameData = true;
			}
			else
			{
				canSaveGame = false;
				isAssemblingSaveGameData = false;

			}
		}
	}
}

void ASideScrollerCharacter::LoadGameLogic()
{
	if (!hasCompletedLoadGame)
	{
		InitLoadGame();

		hasCompletedLoadGame = true;
		isAssemblingSaveGameData = false;
	}
}

#pragma region Save/Load Logic [SideScrollerSaveGame]
void ASideScrollerCharacter::InitSaveGame()
{

	class USideScrollerSaveGame* SaveGameInstance = Cast<USideScrollerSaveGame>(UGameplayStatics::CreateSaveGameObject(USideScrollerSaveGame::StaticClass()));

	if (SaveGameInstance->IsValidLowLevel())
	{
		SaveGameInstance->PawnScoreInstance = CharacterStats.score;
		
		SaveGameInstance->PlayerSaveSlotDate = FDateTime::Now();

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerSaveSlotName, SaveGameInstance->UserIndex);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Game saved!")), true);


	}

	else
	{
		class USideScrollerSaveGame* SaveGameInstance_2 = Cast<USideScrollerSaveGame>(UGameplayStatics::CreateSaveGameObject(USideScrollerSaveGame::StaticClass()));

		if (!SaveGameInstance_2) 
			return;
		else 
		{
			SaveGameInstance_2->PawnScoreInstance = CharacterStats.score;

			SaveGameInstance_2->PlayerSaveSlotDate = FDateTime::Now();

			UGameplayStatics::SaveGameToSlot(SaveGameInstance_2, SaveGameInstance_2->PlayerSaveSlotName, SaveGameInstance_2->UserIndex);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Game saved!")), true);

		}

	}
}

void ASideScrollerCharacter::InitLoadGame()
{
	if (this->IsValidLowLevel())
	{
		class USideScrollerGameInstance* gInstance = Cast<USideScrollerGameInstance>(GetGameInstance());

		if (gInstance)
		{
			if (gInstance->hasDied) {
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString(TEXT("Loading game...")), true);

				const FString SaveSlotName = FString(TEXT("PlayerSaveSlot"));

				if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
				{
					class USideScrollerSaveGame* LoadInstance = Cast<USideScrollerSaveGame>(UGameplayStatics::CreateSaveGameObject(USideScrollerSaveGame::StaticClass()));

					if (LoadInstance - IsValidLowLevel())
					{
						LoadInstance = Cast<USideScrollerSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadInstance->PlayerSaveSlotName, LoadInstance->UserIndex));
						CharacterStats.score = LoadInstance->PawnScoreInstance;

						GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Game loaded from Save!")), true);

						this->SetCoinsFromLoad();

					}
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString(TEXT("No save game found.")), true);
			}

		}
		else 
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString(TEXT("Player not dead yet!")), true);
		}

	}
}


