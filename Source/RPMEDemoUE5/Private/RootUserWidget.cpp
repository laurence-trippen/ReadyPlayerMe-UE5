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
	// UE_LOG(LogTemp, Warning, TEXT("Download Handled"));
	// if (!ItemImage || !Texture) return;
	// ItemImage->SetBrushFromTexture(Texture);

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
	
	FAvatarSaveGameData TestAvatarSaveData;
	TestAvatarSaveData.Name = "I got saved";
	TestAvatarSaveData.Url = "https://models.readyplayer.me/6405da175167081fc2edcb0d.glb";

	FAvatarSaveGameData TestAvatarSaveData2;
	TestAvatarSaveData2.Name = "I got saved too";
	TestAvatarSaveData2.Url = "https://models.readyplayer.me/6405da175167081fc2edcb0d.glb";

	SaveGameInstance->Avatars.Add(TestAvatarSaveData);
	SaveGameInstance->Avatars.Add(TestAvatarSaveData2);

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SlotName, SaveGameInstance->UserIndex);
}


void URootUserWidget::LoadAvatars()
{
	UAvatarSaveGame* LoadGameInstance = Cast<UAvatarSaveGame>(UGameplayStatics::CreateSaveGameObject(UAvatarSaveGame::StaticClass()));

	bool bSaveGameExists = UGameplayStatics::DoesSaveGameExist(LoadGameInstance->SlotName, LoadGameInstance->UserIndex);

	if (bSaveGameExists == false) return;

	LoadGameInstance = Cast<UAvatarSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SlotName, LoadGameInstance->UserIndex));

	for (auto avatar : LoadGameInstance->Avatars)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, avatar.Name);
	}
}
