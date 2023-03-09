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

/**
 * 
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

	UFUNCTION()
	void HandleDownloadImageCompleted(UTexture2D* Texture);

	UFUNCTION()
	void HandleDownloadImageFailed(const FString& ErrorMessage);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameLabel;
};
