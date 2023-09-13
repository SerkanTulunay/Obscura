// Fill out your copyright notice in the Description page of Project Settings.


#include "WindGuideActor.h"

#include "Components/AudioComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

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
	Super::Tick(DeltaTime);
	if(!AudioComp->IsPlaying())
	{
		AudioComp->Play();
	}

	ChangeAudioLocation();
}

void AWindGuideActor::ChangeAudioLocation()
{

	if(SplineCount == SplineComp->GetNumberOfSplinePoints())
	{
		return;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("%f"),(UGameplayStatics::GetPlayerController(this,0)->GetPawn()->GetActorLocation() - SplineComp->GetLocationAtSplinePoint(SplineCount,ESplineCoordinateSpace::World)).Length());
		if((UGameplayStatics::GetPlayerController(this,0)->GetPawn()->GetActorLocation() - SplineComp->GetLocationAtSplinePoint(SplineCount,ESplineCoordinateSpace::World)).Length() < 200)
		{
			UE_LOG(LogTemp,Warning,TEXT("MOVED TO %i" ),SplineCount);
			SplineCount++;
			AudioComp->SetWorldTransform(SplineComp->GetTransformAtSplinePoint(SplineCount, ESplineCoordinateSpace::World));
		}
	}
	
}

