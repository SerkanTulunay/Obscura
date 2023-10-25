// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class OBSCURA_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* FinishLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* StartingPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomWeight = 0.5f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//bool bHasBeenPassed = false;
};
