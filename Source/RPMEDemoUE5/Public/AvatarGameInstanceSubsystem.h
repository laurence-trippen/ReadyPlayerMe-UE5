// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AvatarGameInstanceSubsystem.generated.h"

// Forward Declarations
class UReadyPlayerMeRenderLoader;

/**
 * Game instance wide subsystem for accessing Ready Player Me specific instances.
 */
UCLASS()
class RPMEDEMOUE5_API UAvatarGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    // Begin USubsystem

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // virtual void Deinitialize() override;

    // End USubsystem

    const UReadyPlayerMeRenderLoader* GetAvatar2DLoader() const;

private:
    UPROPERTY()
    UReadyPlayerMeRenderLoader* Avatar2DLoader;
};
