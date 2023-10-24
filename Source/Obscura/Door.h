// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class OBSCURA_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* KeyMesh;
	UPROPERTY(EditAnywhere)
	UChildActorComponent* KeyActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//void OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul);
	
	//void SetOverlapEventTrue();

	UPROPERTY(EditAnywhere)
	bool bIsLocked = true;
	
	UPROPERTY(EditAnywhere)
	bool bIsFuseDoor;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TeleportLocationMesh;

};
