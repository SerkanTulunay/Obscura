// Fill out your copyright notice in the Description page of Project Settings.
#include "FuseBox.h"
#include "MyCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
AFuseBox::AFuseBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FuseBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>("FuseBoxMesh");
	AudioComp = CreateDefaultSubobject<UAudioComponent>("HintAudio");
	FuseBoxMesh->SetupAttachment(RootComponent);
	AudioComp->SetupAttachment(FuseBoxMesh);
}
// Called when the game starts or when spawned
void AFuseBox::BeginPlay()
{
	Super::BeginPlay();
	FuseBoxMesh->OnComponentBeginOverlap.AddDynamic(this,&AFuseBox::OverlapBegin);
	PlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
}
// Called every frame
void AFuseBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerCharacter)
	{
		if(PlayerCharacter->TotalFuses == TotalFuseToCollect)
		{
			AudioComp->SetActive(true);
		}
		else
		{
			AudioComp->SetActive(false);
		}
	}

}
void AFuseBox::PlayHintSound()
{
	AudioComp->SetActive(true);
	AudioComp->Play();
}
void AFuseBox::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("%i"),Player->TotalFuses);
		if(Player->TotalFuses == TotalFuseToCollect)
		{
			UGameplayStatics::PlaySoundAtLocation(this,AllFuseFoundSound,GetActorLocation());
			Player->bHasKey = true;
			AudioComp->Sound = FuseBoxOn;
			AudioComp->Play();
		}

	}
}