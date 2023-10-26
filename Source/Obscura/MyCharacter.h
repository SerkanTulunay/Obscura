// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/App.h"
#include "Sound/SoundCue.h"
#include "RunningEnemy.h"
#include "MyCharacter.generated.h"

UCLASS()
class OBSCURA_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Respawn();
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsHiding = false;

	bool bHasKey = false;

	int TotalFuses;

	UPROPERTY(EditAnywhere)
	float DefaultSpehereRadius = 400;

	float SphereRadius = DefaultSpehereRadius;

	UPROPERTY(EditAnywhere)
	float MaxRadius = 3000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess = "true"))
	float SphereGrowthRate = 80;
	
	//void TakeDamage();
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int ControllerIndex;

private:

	//Variable
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Cam;

	FRotator TargetRotation;
	
	FHitResult HideSpotHit;

	FCollisionQueryParams QueryParams;
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	FVector HideSpotLocation;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	bool bCanHide = false;

	bool bIsMoving = false;

	FVector SpawnPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float StunCooldown;
	float StunTimer = 0;

	bool StunAvailable = false;

	bool bSendPulse = false;

	TArray<FHitResult> OutHits;
	
//sounds
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* NearLockerSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* EnteringHideSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ExitingHideSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* StepSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* WallBumpSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* TurnSwoosh;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* DoorBumpSound;
	UPROPERTY(EditAnywhere,Category = "Sounds")
	USoundCue* DoorUnlocking;
	UPROPERTY(EditAnywhere,Category="Sounds")
	USoundCue* DoorOpening;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* StunActivation;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* StunAvailableSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	UAudioComponent* PlayerAudioComponent;
	

	
	//Functions
	UFUNCTION(BlueprintCallable)
	void ToggleHide();
	void StunEnemy();
	bool ScanHidePlace();
	void StartPulse();
	UFUNCTION(BlueprintCallable)
	void MoveHorizontal(float Axis);
	UFUNCTION(BlueprintCallable)
	void MoveVertical(float Axis);
	UFUNCTION(BlueprintCallable)
	void CameraYaw(float Axis);


private:

};
