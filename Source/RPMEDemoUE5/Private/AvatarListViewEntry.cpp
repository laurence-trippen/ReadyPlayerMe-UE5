// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarListViewEntry.h"
#include "AvatarItem.h"
#include "AvatarPlayerState.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ReadyPlayerMeRenderLoader.h"
#include "ReadyPlayerMeEngineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include <RPMEDemoUE5/RPMEDemoUE5Character.h>
#include <RPMEDemoUE5/RPMEDemoUE5GameMode.h>


void UAvatarListViewEntry::NativeConstruct()
{
	Super::NativeConstruct();

	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();

	// This code is disabled because UReadyPlayerMeRenderLoader it seems that this
	// class can not handle multiple Load() calls at the same time.
	/*
	UReadyPlayerMeEngineSubsystem* ReadyPlayerMeSubsystem = GEngine->GetEngineSubsystem<UReadyPlayerMeEngineSubsystem>();
	if (ReadyPlayerMeSubsystem)
	{
		Avatar2DLoader = ReadyPlayerMeSubsystem->GetAvatar2DLoader();
	}
	*/

	ChooseButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleChooseButtonClicked);
	DeleteButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleDeleteButtonClicked);
}


void UAvatarListViewEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// Cast List Item to Avatar Item
	AvatarItem = Cast<UAvatarItem>(ListItemObject);
	NameLabel->SetText(FText::FromString(AvatarItem->GetName()));

	if (!Avatar2DLoader) return;

	// Hook Download Delegates
	TMap<EAvatarMorphTarget, float> BlendShapes;

	FDownloadImageCompleted DownloadImageCompletedDelegate;
	DownloadImageCompletedDelegate.BindUFunction(this, "HandleDownloadImageCompleted");

	FDownloadImageFailed DownloadImageFailedDelegate;
	DownloadImageFailedDelegate.BindUFunction(this, "HandleDownloadImageFailed");

	Avatar2DLoader->Load(
		AvatarItem->GetUrl(),
		ERenderSceneType::FullBodyPortrait,
		BlendShapes,
		DownloadImageCompletedDelegate,
		DownloadImageFailedDelegate
	);
}


void UAvatarListViewEntry::HandleDownloadImageCompleted(UTexture2D* Texture)
{
	if (!Texture) return;

	IconImage->SetBrushFromTexture(Texture);
}


void UAvatarListViewEntry::HandleDownloadImageFailed(const FString& ErrorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Download Failed"));
}


void UAvatarListViewEntry::HandleChooseButtonClicked()
{
	if (!AvatarItem) return;


	// Switch Avatar
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!Character) return;

	ARPMEDemoUE5Character* ThirdPersonCharacter = Cast<ARPMEDemoUE5Character>(Character);

	if (!ThirdPersonCharacter) return;

	ThirdPersonCharacter->SwitchAvatar(AvatarItem->GetUrl());


	// Notify RootUserWidget reg. Avatar Choosed
	AAvatarPlayerState* PlayerState = GetOwningPlayerState<AAvatarPlayerState>();
	
	if (!PlayerState) return;

	PlayerState->OnAvatarChoosed.Broadcast(AvatarItem);
}


void UAvatarListViewEntry::HandleDeleteButtonClicked()
{
	// Notify RootUserWidget reg. Avatar Deleted
	AAvatarPlayerState* PlayerState = GetOwningPlayerState<AAvatarPlayerState>();

	if (!PlayerState) return;

	PlayerState->OnAvatarDeleted.Broadcast(AvatarItem);
}
