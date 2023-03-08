// Fill out your copyright notice in the Description page of Project Settings.


#include "RootUserWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "AvatarItem.h"
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

	if (!Avatar2DLoader) return;

	if (ItemImage)
	{
		
	}

	UAvatarItem* TestAvatarItem = NewObject<UAvatarItem>();
	TestAvatarItem->SetName("John 117");

	TArray<UAvatarItem*> Avatars;
	Avatars.Add(TestAvatarItem);

	AvatarListView->SetListItems(Avatars);

	UAvatarItem* TestAvatarItem2 = NewObject<UAvatarItem>();
	TestAvatarItem2->SetName("Mr Mister");

	AvatarListView->AddItem(TestAvatarItem2);
}


void URootUserWidget::HandleDownloadImageCompleted(UTexture2D* Texture)
{
	// UE_LOG(LogTemp, Warning, TEXT("Download Handled"));
	// if (!ItemImage || !Texture) return;
	// ItemImage->SetBrushFromTexture(Texture);

	FString Url = AvatarURLTextInput->GetText().ToString();
	FString Nickname = AvatarNameTextInput->GetText().ToString();

	UAvatarItem* NewAvatarItem = NewObject<UAvatarItem>();
	NewAvatarItem->SetName(Nickname);
	NewAvatarItem->SetUrl(Url);
	NewAvatarItem->SetImage(Texture);

	AvatarListView->AddItem(NewAvatarItem);
}


void URootUserWidget::HandleDownloadImageFailed(const FString& ErrorMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Download Failed"));
}


void URootUserWidget::HandleCreateButtonClicked()
{
	FString Url = AvatarURLTextInput->GetText().ToString();

	// TODO: Validate Url
	// TODO: Validate Name

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
}


void URootUserWidget::HandleCancelButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Cancel Clicked"));
}


void URootUserWidget::ResetState()
{

}
