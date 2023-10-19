// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	TeleportLocationMesh = CreateDefaultSubobject<UStaticMeshComponent>("TeleportMesh");
	DoorMesh->SetupAttachment(RootComponent);
	TeleportLocationMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	DoorMesh->SetGenerateOverlapEvents(false);
	DoorMesh->OnComponentBeginOverlap.AddDynamic(this,&ADoor::OverlapBegin);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul)
{
	OtherActor->SetActorLocation(TeleportLocationMesh->GetComponentLocation());
}

void ADoor::SetOverlapEventTrue()
{
	DoorMesh->SetGenerateOverlapEvents(true);
	DoorMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Overlap);
}

