// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyActor.generated.h"

UCLASS()
class OBSCURA_API AKeyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void PickUp();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	class UBoxComponent* HitBox;
	
	UPROPERTY(EditAnywhere)
	class ADoor* ParentDoor;
};
