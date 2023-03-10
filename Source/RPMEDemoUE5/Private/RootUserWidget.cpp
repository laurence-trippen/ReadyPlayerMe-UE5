// Fill out your copyright notice in the Description page of Project Settings.


#include "RootUserWidget.h"

#include "AvatarItem.h"
#include "AvatarSaveGame.h"
#include "AvatarPlayerState.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"


void URootUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CreateButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleCreateButtonClicked);
	CancelButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleCancelButtonClicked);

	AAvatarPlayerState* PlayerState = GetOwningPlayerState<AAvatarPlayerState>();
	if (PlayerState)
	{
		PlayerState->OnAvatarChoosed.AddUniqueDynamic(this, &URootUserWidget::HandleAvatarChoosed);
		PlayerState->OnAvatarDeleted.AddUniqueDynamic(this, &URootUserWidget::HandleAvatarDeleted);
	}

	LoadAvatars();
}


void URootUserWidget::HandleCreateButtonClicked()
{
	FString Url = AvatarURLTextInput->GetText().ToString();
	FString Nickname = AvatarNameTextInput->GetText().ToString();

	// TODO: Validate Url
	// TODO: Validate Name

	UAvatarItem* NewAvatarItem = NewObject<UAvatarItem>();
	NewAvatarItem->SetName(Nickname);
	NewAvatarItem->SetUrl(Url);

	AvatarListView->AddItem(NewAvatarItem);

	SaveAvatars();
	ResetState();
}


void URootUserWidget::HandleCancelButtonClicked()
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cancel Clicked"));

	ResetState();
}


void URootUserWidget::HandleAvatarChoosed(UAvatarItem* ChoosedAvatar)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ChoosedAvatar->GetName());

	ItemTitle->SetText(FText::FromString(ChoosedAvatar->GetName()));

	// Save current set Avatar for next app launch
	SaveAvatars(ChoosedAvatar);
}


void URootUserWidget::HandleAvatarDeleted(UAvatarItem* DeletedAvatar)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, DeletedAvatar->GetName());

	AvatarListView->RemoveItem(DeletedAvatar);

	SaveAvatars();
}


void URootUserWidget::ResetState()
{
	AvatarNameTextInput->SetText(FText::FromString(""));
	AvatarURLTextInput->SetText(FText::FromString(""));
}


void URootUserWidget::SaveAvatars(UAvatarItem* CurrentAvatar)
{
	UAvatarSaveGame* SaveGameInstance = Cast<UAvatarSaveGame>(UGameplayStatics::CreateSaveGameObject(UAvatarSaveGame::StaticClass()));
	
	// Save Current Avatar if passed
	if (CurrentAvatar)
	{
		FAvatarSaveGameData CurrentAvatarSaveData;
		CurrentAvatarSaveData.Name = CurrentAvatar->GetName();
		CurrentAvatarSaveData.Url = CurrentAvatar->GetUrl();

		SaveGameInstance->CurrentAvatar = CurrentAvatarSaveData;
	}

	// Save Avatars
	TArray<UObject*> RawItems = AvatarListView->GetListItems();

	for (auto RawItem : RawItems)
	{
		UAvatarItem* CastedItem = Cast<UAvatarItem>(RawItem);

		FAvatarSaveGameData AvatarSaveData;
		AvatarSaveData.Name = CastedItem->GetName();
		AvatarSaveData.Url = CastedItem->GetUrl();

		SaveGameInstance->Avatars.Add(AvatarSaveData);
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SlotName, SaveGameInstance->UserIndex);
}


void URootUserWidget::LoadAvatars()
{
	UAvatarSaveGame* LoadGameInstance = Cast<UAvatarSaveGame>(UGameplayStatics::CreateSaveGameObject(UAvatarSaveGame::StaticClass()));

	// IMPORTANT: Check first if SaveGame .sav exists before loading it. Otherwise this will cause an Access violation.
	bool bSaveGameExists = UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SlotName, LoadGameInstance->UserIndex);
	if (bSaveGameExists == false) return;

	LoadGameInstance = Cast<UAvatarSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SlotName, LoadGameInstance->UserIndex));

	for (auto AvatarLoadData : LoadGameInstance->Avatars)
	{
		UAvatarItem* NewAvatarItem = NewObject<UAvatarItem>();
		NewAvatarItem->SetName(AvatarLoadData.Name);
		NewAvatarItem->SetUrl(AvatarLoadData.Url);

		AvatarListView->AddItem(NewAvatarItem);
	}

	// Default case; user never selected an Avatar 
	if (LoadGameInstance->CurrentAvatar.Name.IsEmpty() || LoadGameInstance->CurrentAvatar.Url.IsEmpty())
	{
		if (ItemTitle) ItemTitle->SetText(FText::FromString(TEXT("Default Avatar")));
	}
	else
	{
		if (ItemTitle) ItemTitle->SetText(FText::FromString(LoadGameInstance->CurrentAvatar.Name));
	}
}
