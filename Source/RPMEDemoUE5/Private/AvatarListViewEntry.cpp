// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarListViewEntry.h"
#include "AvatarItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UAvatarListViewEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UAvatarItem* Item = Cast<UAvatarItem>(ListItemObject);
	NameLabel->SetText(FText::FromString(Item->GetName()));
	IconImage->SetBrushFromTexture(Item->GetImage());
}
