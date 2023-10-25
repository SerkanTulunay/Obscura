// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HintInterface.h"
#include "GameFramework/Actor.h"
#include "Fuse.generated.h"

UCLASS()
class OBSCURA_API AFuse : public AActor, public IHintInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PlayHintSound() override;
private:
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FuseMesh;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComp

	UPROPERTY(EditAnywhere)
	USoundBase* PickUpSound;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul);

};
