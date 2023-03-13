// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AvatarSaveGame.generated.h"

/**
 * This struct describes an SaveGameData entry for an Avatar.
 */
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
 * Custom derived USaveGame class for persisting user added Ready Player Me
 * Avatars and last used Avatar.
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

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FAvatarSaveGameData CurrentAvatar;
};
