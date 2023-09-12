// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	UPROPERTY(BlueprintReadWrite)
	bool bIsHiding = false;

	void TakeDamage();

private:

	//Variable
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Cam;

	
	FHitResult HideSpotHit;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	FVector HideSpotLocation;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess))
	bool bCanHide = false;

	UPROPERTY(EditAnywhere)
	USoundBase* NearLockerSound;
	UPROPERTY(EditAnywhere)
	USoundBase* EnteringHideSound;
	UPROPERTY(EditAnywhere)
	USoundBase* ExitingHideSound;
	
//	UPROPERTY(EditAnywhere, Category = "sound")
//	class USoundBase* HideSound;

//	UPROPERTY(EditAnywhere, Category = "sound")
	//class USoundBase* UnHideSound;
	
	//Functions
	void ToggleHide();
	bool ScanHidePlace();
	void Run();
	void MoveHorizontal(float Axis);
	void MoveVertical(float Axis);
	void CameraYaw(float Axis);

private:

};
