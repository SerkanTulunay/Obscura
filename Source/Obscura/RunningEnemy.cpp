// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningEnemy.h"

#include "MyCharacter.h"


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
	SpawnPoint = GetActorLocation();
	
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
		bIsStunned = false;
	}

}

void ARunningEnemy::Attack()
{
	const float Radius = 250.f;


	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult PlayerHit;

	bool bhit  = GetWorld()->SweepSingleByChannel(PlayerHit, this->GetActorLocation(), this->GetActorLocation(), FQuat::Identity, ECC_WorldDynamic, FCollisionShape::MakeSphere(Radius), TraceParams);
	if(!bIsStunned)
	{
		if(AMyCharacter* Player = Cast<AMyCharacter>(PlayerHit.GetActor()))
		{
			Player->Respawn();
			Health = 2;
			SetActorLocation(SpawnPoint);
			UGameplayStatics::PlaySoundAtLocation(this, AttackHitSound, GetActorLocation());
		}
	}
}

void ARunningEnemy::BecomeStunned()
{
	if(bIsAttacking)
	{
		
	bIsStunned = true;
	StunTimer = 2;
	UGameplayStatics::PlaySoundAtLocation(this, GetStunnedSound, GetActorLocation());
	if (Health>0)
	{
		Health-=1;
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
		Destroy();
	}
	}
}

// Called to bind functionality to input
void ARunningEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

