// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningEnemy.h"

// Sets default values
ARunningEnemy::ARunningEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARunningEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunningEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StunTimer>0)
	{
		StunTimer-=DeltaTime;
	}
	else
	{
		//bIsStunned = false;
	}

}

void ARunningEnemy::BecomeStunned()
{
	//bIsStunned = true;
	StunTimer = 2;
}

// Called to bind functionality to input
void ARunningEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

