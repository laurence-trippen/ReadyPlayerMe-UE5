// Fill out your copyright notice in the Description page of Project Settings.


#include "RootUserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ReadyPlayerMeRenderLoader.h"


void URootUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();

	UE_LOG(LogTemp, Warning, TEXT("Hello UI"));

	if (ItemTitle)
	{
		ItemTitle->SetText(FText::FromString(TEXT("laurence_trippen")));
	}

	if (!Avatar2DLoader) return;

	if (ItemImage)
	{
		TMap<EAvatarMorphTarget, float> BlendShapes;

		FDownloadImageCompleted DownloadImageCompletedDelegate;
		DownloadImageCompletedDelegate.BindUFunction(this, "HandleDownloadImageCompleted");

		FDownloadImageFailed DownloadImageFailedDelegate;
		DownloadImageFailedDelegate.BindUFunction(this, "HandleDownloadImageFailed");

		Avatar2DLoader->Load(
			"https://models.readyplayer.me/6405da175167081fc2edcb0d.glb", 
			ERenderSceneType::FullBodyPortrait,
			BlendShapes,
			DownloadImageCompletedDelegate,
			DownloadImageFailedDelegate
		);
	}
}


void URootUserWidget::HandleDownloadImageCompleted(UTexture2D* Texture)
{
	UE_LOG(LogTemp, Warning, TEXT("Download Handled"));

	if (!ItemImage || !Texture) return;

	ItemImage->SetBrushFromTexture(Texture);
}


void URootUserWidget::HandleDownloadImageFailed(const FString& ErrorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Download Failed"));
}
