// Fill out your copyright notice in the Description page of Project Settings.


#include "FuseBox.h"

#include "MyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AFuseBox::AFuseBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FuseBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>("FuseBoxMesh");
	FuseBoxMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFuseBox::BeginPlay()
{
	Super::BeginPlay();
	FuseBoxMesh->OnComponentBeginOverlap.AddDynamic(this,&AFuseBox::OverlapBegin);
}

// Called every frame
void AFuseBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuseBox::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{
		if(Player->TotalFuses == TotalFuseToCollect)
		{
			Player->bHasKey = true;
		}
		else
		{
			for(int i = TotalFuseToCollect - Player->TotalFuses; TotalFuseToCollect >= 0; i--)
			{
				//Play Indicator sound for missing sound
			}
		}
	}
}