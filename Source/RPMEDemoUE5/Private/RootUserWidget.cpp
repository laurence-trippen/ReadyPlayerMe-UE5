// Fill out your copyright notice in the Description page of Project Settings.


#include "RootUserWidget.h"

#include "Components/TextBlock.h"
#include "ReadyPlayerMeRenderLoader.h"


void URootUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Avatar2DLoader = NewObject<UReadyPlayerMeRenderLoader>();

	UE_LOG(LogTemp, Warning, TEXT("Hello UI"));

	if (ItemTitle)
	{
		ItemTitle->SetText(FText::FromString(TEXT("Hello UI!!")));

		if (Avatar2DLoader)
		{
			ItemTitle->SetText(FText::FromString(TEXT("Loader Set")));
		}
	}
}
