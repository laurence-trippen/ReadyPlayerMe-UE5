// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarListViewEntry.h"
#include "AvatarItem.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ReadyPlayerMeRenderLoader.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#include <RPMEDemoUE5/RPMEDemoUE5Character.h>


void UAvatarListViewEntry::NativeConstruct()
{
	Super::NativeConstruct();

	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();

	ChooseButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleChooseButtonClicked);
	DeleteButton->OnClicked.AddUniqueDynamic(this, &ThisClass::HandleDeleteButtonClicked);
}


void UAvatarListViewEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// Cast List Item to Avatar Item
	AvatarItem = Cast<UAvatarItem>(ListItemObject);
	NameLabel->SetText(FText::FromString(AvatarItem->GetName()));

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

	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!character) return;

	ARPMEDemoUE5Character* thirdPersonCharacter = Cast<ARPMEDemoUE5Character>(character);

	if (!thirdPersonCharacter) return;

	thirdPersonCharacter->SwitchAvatar(AvatarItem->GetUrl());
}


void UAvatarListViewEntry::HandleDeleteButtonClicked()
{

}
