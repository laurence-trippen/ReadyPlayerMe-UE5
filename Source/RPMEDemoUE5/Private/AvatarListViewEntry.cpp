// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarListViewEntry.h"
#include "AvatarItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ReadyPlayerMeRenderLoader.h"


void UAvatarListViewEntry::NativeConstruct()
{
	Super::NativeConstruct();

	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();
}


void UAvatarListViewEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// Cast List Item to Avatar Item
	UAvatarItem* Item = Cast<UAvatarItem>(ListItemObject);
	NameLabel->SetText(FText::FromString(Item->GetName()));

	// Hook Download Delegates
	TMap<EAvatarMorphTarget, float> BlendShapes;

	FDownloadImageCompleted DownloadImageCompletedDelegate;
	DownloadImageCompletedDelegate.BindUFunction(this, "HandleDownloadImageCompleted");

	FDownloadImageFailed DownloadImageFailedDelegate;
	DownloadImageFailedDelegate.BindUFunction(this, "HandleDownloadImageFailed");

	Avatar2DLoader->Load(
		Item->GetUrl(),
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
