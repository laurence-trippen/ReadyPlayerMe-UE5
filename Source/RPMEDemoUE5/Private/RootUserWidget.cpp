// Fill out your copyright notice in the Description page of Project Settings.


#include "RootUserWidget.h"

#include "AvatarItem.h"
#include "AvatarSaveGame.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "ReadyPlayerMeRenderLoader.h"


void URootUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();

	CreateButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleCreateButtonClicked);
	CancelButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleCancelButtonClicked);

	if (ItemTitle)
	{
		ItemTitle->SetText(FText::FromString(TEXT("laurence_trippen")));
	}

	LoadAvatars();
}


void URootUserWidget::HandleDownloadImageCompleted(UTexture2D* Texture)
{
	if (!Texture) return;

	FString Url = FormCache.Url;
	FString Nickname = FormCache.Name;

	UAvatarItem* NewAvatarItem = NewObject<UAvatarItem>();
	NewAvatarItem->SetName(Nickname);
	NewAvatarItem->SetUrl(Url);
	NewAvatarItem->SetImage(Texture);

	AvatarListView->AddItem(NewAvatarItem);

	SaveAvatars();
}


void URootUserWidget::HandleDownloadImageFailed(const FString& ErrorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Download Failed"));
}


void URootUserWidget::HandleCreateButtonClicked()
{
	FString Url = AvatarURLTextInput->GetText().ToString();
	FString Nickname = AvatarNameTextInput->GetText().ToString();

	// TODO: Validate Url
	// TODO: Validate Name

	FormCache.Name = Nickname;
	FormCache.Url = Url;

	TMap<EAvatarMorphTarget, float> BlendShapes;

	FDownloadImageCompleted DownloadImageCompletedDelegate;
	DownloadImageCompletedDelegate.BindUFunction(this, "HandleDownloadImageCompleted");

	FDownloadImageFailed DownloadImageFailedDelegate;
	DownloadImageFailedDelegate.BindUFunction(this, "HandleDownloadImageFailed");

	Avatar2DLoader->Load(
		Url,
		ERenderSceneType::FullBodyPortrait,
		BlendShapes,
		DownloadImageCompletedDelegate,
		DownloadImageFailedDelegate
	);

	ResetState();
}


void URootUserWidget::HandleCancelButtonClicked()
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cancel Clicked"));

	ResetState();
}


void URootUserWidget::ResetState()
{
	AvatarNameTextInput->SetText(FText::FromString(""));
	AvatarURLTextInput->SetText(FText::FromString(""));
}


void URootUserWidget::SaveAvatars()
{
	UAvatarSaveGame* SaveGameInstance = Cast<UAvatarSaveGame>(UGameplayStatics::CreateSaveGameObject(UAvatarSaveGame::StaticClass()));
	
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

	for (auto avatar : LoadGameInstance->Avatars)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, avatar.Name);
	}
}
