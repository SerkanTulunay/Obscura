// Fill out your copyright notice in the Description page of Project Settings.


#include "WindGuideActor.h"
#include "Components/AudioComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWindGuideActor::AWindGuideActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>("Spline");
	AudioCarrier = CreateDefaultSubobject<UStaticMeshComponent>("AudioCarrier");
	AudioComp = CreateDefaultSubobject<UAudioComponent>("WindAudio");
	
	if(SplineComp && AudioComp)
	{
		SetRootComponent(SplineComp);
		AudioComp->SetupAttachment(AudioCarrier);
	}
}

// Called when the game starts or when spawned
void AWindGuideActor::BeginPlay()
{
	Super::BeginPlay();
	AudioComp->SetWorldTransform(SplineComp->GetTransformAtSplinePoint(SplineCount, ESplineCoordinateSpace::World));
}

// Called every frame
void AWindGuideActor::Tick(float DeltaTime)
{
	PlayerLocation = UGameplayStatics::GetPlayerController(this,0)->GetPawn()->GetActorLocation();
	Super::Tick(DeltaTime);
	if(!AudioComp->IsPlaying() && SplineCount != SplineComp->GetNumberOfSplinePoints())
	{
		AudioComp->Play();
	}

	ChangeAudioLocation();
}

void AWindGuideActor::ChangeAudioLocation()
{
	const float CurrentDistance = SplineComp->GetDistanceAlongSplineAtSplineInputKey(SplineComp->FindInputKeyClosestToWorldLocation(PlayerLocation)) + DistanceOffset;
	const FVector NewLocation = SplineComp->GetLocationAtDistanceAlongSpline(CurrentDistance,ESplineCoordinateSpace::World);
	AudioCarrier->SetWorldLocation(NewLocation);
}

