// Fill out your copyright notice in the Description page of Project Settings.


#include "ObscuraSettings.h"


UObscuraSettings::UObscuraSettings(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	//Charging enemy
	ChargingEnemyMoveSpeed = 100.f;

	ChargingEnemyVolume =0.5f;

	//Attacking enemy
	AttackingEnemyMoveSpeed = 100.f;

	AttackingEnemyRange= 300.f;

	AttackingEnemyAttackDelay =4.f;

	AttackingEnemyIdleVolume = 0.6f;
	
	//Patrolling enemy

	PatrollingEnemyMoveSpeed =100.f;

	PatrollingEnemyRange = 300.f;

	PatrollingEnemyAttackDelay=4.f;
	
	PatrollingEnemyIdleVolume = 0.2f;

	//Player
	MoveCD =0.3f;

	StunCooldown =2.5f;

}

UObscuraSettings* UObscuraSettings::GetSettings()
{
	return Cast<UObscuraSettings>(UObscuraSettings::GetGameUserSettings());
	

}
