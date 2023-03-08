// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AvatarItem.generated.h"

/**
 * 
 */
UCLASS()
class RPMEDEMOUE5_API UAvatarItem : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Url;

	UPROPERTY()
	UTexture2D* Image;

public:
	UFUNCTION()
	void SetName(const FString& NewName);

	UFUNCTION()
	const FString& GetName() const;

	UFUNCTION()
	void SetUrl(const FString& NewUrl);

	UFUNCTION()
	const FString& GetUrl() const;

	UFUNCTION()
	void SetImage(UTexture2D* NewImage);

	UFUNCTION()
	const UTexture2D* GetImage() const;
};
