// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindGuideActor.generated.h"

UCLASS()
class OBSCURA_API AWindGuideActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindGuideActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Variables
	UPROPERTY(VisibleAnywhere,Category="Spline",meta=(AllowPrivateAccess))
	class USplineComponent* SplineComp;

	FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere,Category="Spline",meta=(AllowPrivateAccess))
	float SplineSpeed = 10;

	UPROPERTY(VisibleAnywhere,Category="Audio",meta=(AllowPrivateAccess))
	UStaticMeshComponent* AudioCarrier;

	UPROPERTY(VisibleAnywhere,Category="Audio",meta=(AllowPrivateAccess))
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere)
	float DistanceOffset = 300;
	
	int SplineCount = 0;

	//Functions
	void ChangeAudioLocation();
};
