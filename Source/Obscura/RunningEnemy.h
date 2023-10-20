// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "RunningEnemy.generated.h"

UCLASS()
class OBSCURA_API ARunningEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunningEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BecomeStunned();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Target;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsStunned;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StunTimer;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* GetStunnedSound;


};
