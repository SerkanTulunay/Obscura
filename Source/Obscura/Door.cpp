// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "RunningEnemy.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	TeleportLocationMesh = CreateDefaultSubobject<UStaticMeshComponent>("TeleportMesh");
	AudioComp = CreateDefaultSubobject<UAudioComponent>("HintAudio");

	DoorMesh->SetupAttachment(RootComponent);
	AudioComp->SetupAttachment(DoorMesh);
	TeleportLocationMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	AudioComp->SetActive(true);
	AudioComp->Play();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::PlayHintSound()
{
	AudioComp->SetActive(true);
	AudioComp->Play();
}

void ADoor::ToggleActiveEnemies()
{
	for(AActor* OldA : OldActors)
	{
		OldA->SetActorTickEnabled(false);
		
	}
	for(AActor* NewA : NewActors)
	{
		NewA->SetActorTickEnabled(true);
	}

}


