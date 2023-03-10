// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AvatarPlayerState.generated.h"

// Forward Declarations
class UAvatarItem;


// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAvatarChoosed, UAvatarItem*, ChoosedAvatar);

/**
 * 
 */
UCLASS()
class RPMEDEMOUE5_API AAvatarPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnAvatarChoosed OnAvatarChoosed;
};
