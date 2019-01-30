// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SideScrollerCharacter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData
{

	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float health;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int32 score;

};

UCLASS()
class SIDESCROLLER_API ASideScrollerCharacter : public ACharacter
{
	GENERATED_BODY()

private: 

	bool isAssemblingSaveGameData;
	bool hasCompletedCustomSaveGame;
	bool hasCompletedLoadGame;


	static const FName PlayerTagName;

public:
	// Sets default values for this character's properties
	ASideScrollerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FCharacterData CharacterStats;

public:

	void SaveGameLogic();
	void LoadGameLogic();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canSaveGame;

public:

	void InitSaveGame();

	void InitLoadGame();

public:

	bool SaveGameToFile(const FString& FullFilePath);


	bool LoadGameFromFile(const FString& FullFilePath, int32& ScoreSaveData, TArray<FString>& Inventory, FDateTime& SaveTime);

	void CustomeSaveLoadData(FArchive& Ar, int32& ScoreSaveData, TArray<FString>& Inventory, FDateTime& SaveTime);

	UPROPERTY()
	FDateTime SaveGameTime;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCoinsFromLoad();
	
	
};
