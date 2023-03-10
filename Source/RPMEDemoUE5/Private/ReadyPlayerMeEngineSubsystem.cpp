// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadyPlayerMeEngineSubsystem.h"

#include "ReadyPlayerMeRenderLoader.h"

void UReadyPlayerMeEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();
}

UReadyPlayerMeRenderLoader* UReadyPlayerMeEngineSubsystem::GetAvatar2DLoader() const
{
	return Avatar2DLoader;
}
