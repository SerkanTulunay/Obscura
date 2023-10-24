// Fill out your copyright notice in the Description page of Project Settings.


#include "Fuse.h"

#include "MyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AFuse::AFuse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FuseMesh = CreateDefaultSubobject<UStaticMeshComponent>("FuseMesh");
	FuseMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFuse::BeginPlay()
{
	Super::BeginPlay();
	FuseMesh->OnComponentBeginOverlap.AddDynamic(this,&AFuse::OverlapBegin);
}

// Called every frame
void AFuse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuse::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{
		Player->TotalFuses++;
		UE_LOG(LogTemp,Warning,TEXT("FUSE PICKED"));
		Destroy();
	}
}

