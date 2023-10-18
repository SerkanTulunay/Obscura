// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"
#include "Door.h"
#include "Components/BoxComponent.h"

// Sets default values
AKeyActor::AKeyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	ParentDoor = CreateDefaultSubobject<ADoor>("ParentDoor");

	HitBox->OnComponentHit.AddDynamic(this,&AKeyActor::OnHit);
}

// Called when the game starts or when spawned
void AKeyActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKeyActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*OtherActor->GetName());
}



