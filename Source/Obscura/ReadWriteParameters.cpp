// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadWriteParameters.h"
#include "HAL/PlatformFileManager.h"
#include "Serialization/JsonSerializer.h"



UReadWriteParameters::UReadWriteParameters()
{
}

UReadWriteParameters::~UReadWriteParameters()
{
}

TSharedPtr<FJsonObject> UReadWriteParameters::ReadJson(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	FString JsonString = ReadFile(FilePath, bOutSuccess, OutInfoMessage);
	if(!bOutSuccess)
	{
		return nullptr;
	}
	TSharedPtr<FJsonObject> RetJsonObject;
	if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		
	}
}

FString UReadWriteParameters::ReadFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf("File does not exist");
	}
	FString RetString = "";
	if (!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf("No text file in filepath");
		return "";
	}
	return RetString;
}
