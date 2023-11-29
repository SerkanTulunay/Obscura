// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_LoadMainMenu.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAC_LoadMainMenu::UAC_LoadMainMenu()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UAC_LoadMainMenu::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UAC_LoadMainMenu::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_LoadMainMenu::LoadLevel()
{
	UGameplayStatics::OpenLevel(this,"MainMenuLevel");
}

void UAC_LoadMainMenu::OverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("HIT PLAYER AND LOAD NEXT LEVEL"));
	}
}


