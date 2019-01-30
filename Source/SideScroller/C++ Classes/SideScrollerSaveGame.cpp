// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerSaveGame.h"
#include "SideScroller.h"

USideScrollerSaveGame::USideScrollerSaveGame() 
{

	PawnScoreInstance = 0.f;

	Inventory.Add("HeroSword_22");

	PlayerSaveSlotName = FString(TEXT("PlayerSaveSlot"));
	UserIndex = 0;

}




