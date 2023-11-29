// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HintInterface.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class OBSCURA_API ADoor : public AActor, public IHintInterface
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

	virtual void PlayHintSound() override;

	void ToggleActiveEnemies();

	UPROPERTY(EditAnywhere)
	bool bLoadMainMenuDoor = false;
	
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
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta =(AllowPrivateAccess ="true"))
	UAudioComponent* AudioComp;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> NewActors;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> OldActors;
};
