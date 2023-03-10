// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "ReadyPlayerMeEngineSubsystem.generated.h"


// Forward Declarations
class UReadyPlayerMeRenderLoader;


/**
 * 
 */
UCLASS()
class RPMEDEMOUE5_API UReadyPlayerMeEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
    // Begin USubsystem

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // virtual void Deinitialize() override;

    // End USubsystem

    UReadyPlayerMeRenderLoader* GetAvatar2DLoader() const;

private:
    UPROPERTY()
    UReadyPlayerMeRenderLoader* Avatar2DLoader;
};
