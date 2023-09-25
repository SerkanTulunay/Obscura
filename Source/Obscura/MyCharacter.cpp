// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundCue.h"

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
	TargetRotation = GetActorRotation();
	Super::BeginPlay();
	bIsHiding = false;
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ScanHidePlace();
	SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime, 500.f ));
	if(GetActorRotation() == TargetRotation)
		bIsMoving = false;
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAxis("Horizontal",this,&AMyCharacter::MoveHorizontal);
	//PlayerInputComponent->BindAxis("Vertical",this,&AMyCharacter::MoveVertical);
	//PlayerInputComponent->BindAxis("MouseYaw",this,&AMyCharacter::CameraYaw);
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

		UGameplayStatics::PlaySoundAtLocation(HideSpotHit.GetActor(), EnteringHideSound, HideSpotHit.GetActor()->GetActorLocation());
		SetActorRotation(HideSpotHit.GetActor()->GetActorForwardVector().Rotation());
			//Make sound to go into locker
	}
	}
	else
	{
		if(ScanHidePlace())
		{
			UE_LOG(LogTemp,Warning,TEXT("HIDING"));
			bIsHiding = true;
			UGameplayStatics::PlaySoundAtLocation(HideSpotHit.GetActor(), ExitingHideSound, HideSpotHit.GetActor()->GetActorLocation());
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

	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	bCanHide = GetWorld()->SweepSingleByChannel(HideSpotHit, this->GetActorLocation(), this->GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), TraceParams);

	if(bCanHide)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s"),*HideSpotHit.GetComponent()->GetName());
		HideSpotLocation = HideSpotHit.GetActor()->GetActorLocation();
		//make sound and set hidable true
	}
	return bCanHide;
}

void AMyCharacter::Run()
{
}

void AMyCharacter::MoveHorizontal(float Axis)
{
	const float Radius = 1.f;

	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult hit;
	bool MovementBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorRightVector()*Axis*100, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);
	if(!bIsHiding && !MovementBlocked)
		SetActorLocation(GetActorLocation()+GetActorRightVector()*Axis*100);
	if(MovementBlocked)
	{
		//PlayBlockedSound
	}

}

void AMyCharacter::MoveVertical(float Axis)
{
	const float Radius = 1.f;

	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult hit;
	bool MovementBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorForwardVector()*Axis*100, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);
	if(!bIsHiding && !MovementBlocked && !bIsMoving)
		SetActorLocation(GetActorLocation()+GetActorForwardVector()*Axis*100);
	if(MovementBlocked)
	{
		//PlayBlockedSound
	}

}

void AMyCharacter::CameraYaw(float Axis)
{
	if(!bIsHiding && !bIsMoving)
	{
		TargetRotation = TargetRotation + FRotator(0,90*Axis,0);
		bIsMoving = true;
	}
	//SetActorRotation(GetActorRotation() + FRotator(0,90*Axis,0));
	//PlayRotationSound
	//SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), GetActorRotation() + FRotator(0,90*Axis,0), FApp::GetDeltaTime(), 0.3f ));
}

