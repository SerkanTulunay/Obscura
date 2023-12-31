// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"
#include "Door.h"
#include "MyCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKeyActor::AKeyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("KeyMesh");
	KeyMesh->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("HintAudio");
	AudioComp->SetupAttachment(KeyMesh);
}

// Called when the game starts or when spawned
void AKeyActor::BeginPlay()
{
	Super::BeginPlay();
	KeyMesh->OnComponentBeginOverlap.AddDynamic(this,&AKeyActor::OverlapBegin);
	AudioComp->SetActive(false);
	AudioComp->Play();
}

// Called every frame
void AKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKeyActor::PlayHintSound()
{
}

void AKeyActor::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	if(AMyCharacter* HitPlayer = Cast<AMyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("Has KEY"));
		AudioComp->SetActive(true);
		HitPlayer->bHasKey = true;
		UGameplayStatics::PlaySoundAtLocation(this,PickUpSound,GetActorLocation());
		Destroy();
	}
}




