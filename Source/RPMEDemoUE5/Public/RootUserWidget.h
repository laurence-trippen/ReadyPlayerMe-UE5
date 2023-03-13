// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RootUserWidget.generated.h"

// Forward Declarations
class UAvatarItem;
class UButton;
class UTextBlock;
class UEditableText;
class UImage;
class UListView;
class UTexture2D;
class UReadyPlayerMeRenderLoader;


/**
 * Derived UserWidget which is the Root of the UMG tree.
 * This class binds UMG widgets with (BindWidget) for C++ UI access.
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
	UPROPERTY()
	UReadyPlayerMeRenderLoader* Avatar2DLoader;

	UFUNCTION()
	void HandleCreateButtonClicked();

	UFUNCTION()
	void HandleCancelButtonClicked();

	UFUNCTION()
	void HandleAvatarChoosed(UAvatarItem* ChoosedAvatar);

	UFUNCTION()
	void HandleAvatarDeleted(UAvatarItem* DeletedAvatar);

	UFUNCTION()
	void HandleDownloadImageCompleted(UTexture2D* Texture);

	UFUNCTION()
	void HandleDownloadImageFailed(const FString& ErrorMessage);

	UFUNCTION()
	void ResetState();

	UFUNCTION()
	void SaveAvatars(UAvatarItem* CurrentAvatar = nullptr);

	UFUNCTION()
	void LoadAvatars();

	UFUNCTION()
	void SetCurrentAvatarUI(const FString& Url, const FString& Name);
};
