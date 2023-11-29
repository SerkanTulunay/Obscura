// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ObscuraSettings.generated.h"

/**
 * 
 */
UCLASS()
class OBSCURA_API UObscuraSettings : public UGameUserSettings
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UObscuraSettings* GetSettings();
	



	//Charging enemy
	UPROPERTY(Config, BlueprintReadWrite)
	float ChargingEnemyMoveSpeed;

	UPROPERTY(Config, BlueprintReadWrite)
	float ChargingEnemyVolume;

	//Attacking enemy
	UPROPERTY(Config, BlueprintReadWrite)
	float AttackingEnemyMoveSpeed;

	UPROPERTY(Config, BlueprintReadWrite)
	float AttackingEnemyRange;

	UPROPERTY(Config, BlueprintReadWrite)
	float AttackingEnemyAttackDelay;

	UPROPERTY(Config, BlueprintReadWrite)
	float AttackingEnemyIdleVolume;
	
	//Patrolling enemy
	UPROPERTY(Config, BlueprintReadWrite)
	float PatrollingEnemyMoveSpeed;

	UPROPERTY(Config, BlueprintReadWrite)
	float PatrollingEnemyRange;

	UPROPERTY(Config, BlueprintReadWrite)
	float PatrollingEnemyAttackDelay;

	UPROPERTY(Config, BlueprintReadWrite)
	float PatrollingEnemyIdleVolume;

	//Player
	UPROPERTY(Config, BlueprintReadWrite)
	float MoveCD;

	UPROPERTY(Config, BlueprintReadWrite)
	float StunCooldown;


	
};
