// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AvatarListViewEntry.generated.h"

// Forward Declarations
class UTextBlock;
class UImage;


/**
 * 
 */
UCLASS(Abstract)
class RPMEDEMOUE5_API UAvatarListViewEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameLabel;
};
