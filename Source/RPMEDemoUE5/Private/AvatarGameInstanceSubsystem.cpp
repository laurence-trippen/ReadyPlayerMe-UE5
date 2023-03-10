// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarGameInstanceSubsystem.h"

#include "ReadyPlayerMeRenderLoader.h"

void UAvatarGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();
}

const UReadyPlayerMeRenderLoader* UAvatarGameInstanceSubsystem::GetAvatar2DLoader() const
{
	return Avatar2DLoader;
}
