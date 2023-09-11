// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;

	Cam = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	Cam->SetupAttachment(RootComponent);;
	Cam->SetRelativeLocation(FVector(0,0,40));

	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	bIsHiding = false;
	
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ScanHidePlace();
	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal",this,&AMyCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical",this,&AMyCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("MouseYaw",this,&AMyCharacter::CameraYaw);
	PlayerInputComponent->BindAction("Hide",IE_Pressed,this,&AMyCharacter::ToggleHide);
}

void AMyCharacter::ToggleHide()
{
	if(!bIsHiding)
	{
	if(ScanHidePlace())
	{
		UE_LOG(LogTemp,Warning,TEXT("HIDING"));
		bIsHiding = true;
		//UGameplayStatics::PlaySoundAtLocation(this,HideSound , this->GetActorLocation());
			//Make sound to go into locker
	}
	}
	else
	{
		if(ScanHidePlace())
		{
			UE_LOG(LogTemp,Warning,TEXT("HIDING"));
			bIsHiding = true;
			//UGameplayStatics::PlaySoundAtLocation(this,HideSound , this->GetActorLocation());
			//Make sound to go into locker
		}
	UE_LOG(LogTemp,Warning,TEXT("UnHIDING"));

	bIsHiding = false;
	}
	//UGameplayStatics::PlaySoundAtLocation(this, UnHideSound , this->GetActorLocation());
	//make sound to leave locker
	
}

bool AMyCharacter::ScanHidePlace()
{
	const float Radius = 200.f;
	bool bHit;

	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	bHit = GetWorld()->SweepSingleByChannel(HideSpotHit, this->GetActorLocation(), this->GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), TraceParams);

	if(bHit)
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"),*HideSpotHit.GetComponent()->GetName());
		
		//make sound and set hidable true
	}
	return bHit;
}

void AMyCharacter::Run()
{
}

void AMyCharacter::MoveHorizontal(float Axis)
{
	if(!bIsHiding)
	AddMovementInput(GetActorRightVector(),Axis);
}

void AMyCharacter::MoveVertical(float Axis)
{
	if(!bIsHiding)
	AddMovementInput(GetActorForwardVector(),Axis);
}

void AMyCharacter::CameraYaw(float Axis)
{
	if(!bIsHiding)
	AddActorLocalRotation(FRotator(0,Axis,0));
}

