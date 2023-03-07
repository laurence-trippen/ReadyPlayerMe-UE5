// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RootUserWidget.generated.h"

// Forward Declarations
class UTextBlock;
class UReadyPlayerMeRenderLoader;

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

private:
	UPROPERTY(VisibleAnywhere)
	UReadyPlayerMeRenderLoader* Avatar2DLoader;
};
