// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RootUserWidget.generated.h"

// Forward Declarations
class UButton;
class UTextBlock;
class UEditableText;
class UImage;
class UListView;
class UTexture2D;
class UReadyPlayerMeRenderLoader;

struct FCreateAvatarFormCache
{
	FString Name;
	FString Url;
};

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
	UEditableText* AvatarURLTextInput;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableText* AvatarNameTextInput;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CreateButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView* AvatarListView;
	
private:
	FCreateAvatarFormCache FormCache;

	UPROPERTY(VisibleAnywhere)
	UReadyPlayerMeRenderLoader* Avatar2DLoader;

	UFUNCTION()
	void HandleDownloadImageCompleted(UTexture2D* Texture);

	UFUNCTION()
	void HandleDownloadImageFailed(const FString& ErrorMessage);

	UFUNCTION()
	void HandleCreateButtonClicked();

	UFUNCTION()
	void HandleCancelButtonClicked();

	UFUNCTION()
	void ResetState();

	UFUNCTION()
	void SaveAvatars();

	UFUNCTION()
	void LoadAvatars();
};
