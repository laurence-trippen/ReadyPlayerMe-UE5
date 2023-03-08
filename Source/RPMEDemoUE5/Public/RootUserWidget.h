// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RootUserWidget.generated.h"

// Forward Declarations
class UTextBlock;
class UImage;
class UListView;
class UReadyPlayerMeRenderLoader;
class UTexture2D;

/**
 * 
 */
UCLASS(Abstract)
class RPMEDEMOUE5_API URootUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemTitle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView* AvatarListView;
	
private:
	UPROPERTY(VisibleAnywhere)
	UReadyPlayerMeRenderLoader* Avatar2DLoader;

	UFUNCTION()
	void HandleDownloadImageCompleted(UTexture2D* Texture);

	UFUNCTION()
	void HandleDownloadImageFailed(const FString& ErrorMessage);
};
