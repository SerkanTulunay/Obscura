// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FJsonObject;;
/**
 * 
 */
UCLASS()
class OBSCURA_API UReadWriteParameters : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UReadWriteParameters();
	~UReadWriteParameters();
	UFUNCTION(BlueprintCallable)
	static TSharedPtr<FJsonObject> ReadJson(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);

	UFUNCTION(Blueprintable)
	static FString ReadFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);
};
