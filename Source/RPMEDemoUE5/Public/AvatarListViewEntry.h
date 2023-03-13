// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AvatarListViewEntry.generated.h"

// Forward Declarations
class UTextBlock;
class UImage;
class UReadyPlayerMeRenderLoader;
class UButton;
class UAvatarItem;

/**
 * Inherited UserWidget for Ready Player Me Avatar model ListView entries.
 */
UCLASS(Abstract)
class RPMEDEMOUE5_API UAvatarListViewEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	// TODO: Find a way to make this object to a static member without compile errors to have only one instance in memory.
	// Alternatively this could be also accomplished with Dependency-Injection?
	UPROPERTY()
	UReadyPlayerMeRenderLoader* Avatar2DLoader;

	UPROPERTY()
	UAvatarItem* AvatarItem;

	UFUNCTION()
	void HandleDownloadImageCompleted(UTexture2D* Texture);

	UFUNCTION()
	void HandleDownloadImageFailed(const FString& ErrorMessage);

	UFUNCTION()
	void HandleChooseButtonClicked();

	UFUNCTION()
	void HandleDeleteButtonClicked();

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameLabel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ChooseButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* DeleteButton;
};
