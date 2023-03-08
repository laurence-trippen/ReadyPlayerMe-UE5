// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarItem.h"


void UAvatarItem::SetName(const FString& NewName)
{
	Name = NewName;
}


const FString& UAvatarItem::GetName() const
{
	return Name;
}


void UAvatarItem::SetUrl(const FString& NewUrl)
{
	Url = NewUrl;
}


const FString& UAvatarItem::GetUrl() const
{
	return Url;
}

void UAvatarItem::SetImage(UTexture2D* NewImage)
{
	Image = NewImage;
}

const UTexture2D* UAvatarItem::GetImage() const
{
	return Image;
}
