// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AvatarSaveGame.generated.h"


USTRUCT(BlueprintType)
struct FAvatarSaveGameData
{
	// For participating in Unreals Reflection System
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString Url;
};


/**
 * 
 */
UCLASS()
class RPMEDEMOUE5_API UAvatarSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UAvatarSaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FAvatarSaveGameData> Avatars;
};
