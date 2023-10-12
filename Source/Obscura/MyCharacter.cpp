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
	
	if(GetActorRotation().Equals(TargetRotation))//Enables movement if rotation is finished
		bIsMoving = false;


		
	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Hide",IE_Pressed,this,&AMyCharacter::ToggleHide);

	//Old inputs:
	//PlayerInputComponent->BindAxis("Horizontal",this,&AMyCharacter::MoveHorizontal);
	//PlayerInputComponent->BindAxis("Vertical",this,&AMyCharacter::MoveVertical);
	//PlayerInputComponent->BindAxis("MouseYaw",this,&AMyCharacter::CameraYaw);
}

void AMyCharacter::ToggleHide()//Player hides/unhides in locker if in range
{
	if(!bIsHiding)
	{
	if(ScanHidePlace())//Player hides
	{
		bIsHiding = true;

		UGameplayStatics::PlaySoundAtLocation(HideSpotHit.GetActor(), EnteringHideSound, HideSpotHit.GetActor()->GetActorLocation());
		TargetRotation = (HideSpotHit.GetActor()->GetActorForwardVector().Rotation());
	}
	}
	else
	{
		if(ScanHidePlace()) //Player unhides
		{
			bIsHiding = true;
			UGameplayStatics::PlaySoundAtLocation(HideSpotHit.GetActor(), ExitingHideSound, HideSpotHit.GetActor()->GetActorLocation());
		}
	bIsHiding = false;
	}
	
}

bool AMyCharacter::ScanHidePlace()//Sweeps for lockers in vicinity
{
	const float Radius = 200.f;

	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	bCanHide = GetWorld()->SweepSingleByChannel(HideSpotHit, this->GetActorLocation(), this->GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius), TraceParams);

	if(bCanHide)
	{
		HideSpotLocation = HideSpotHit.GetActor()->GetActorLocation();
	}
	return bCanHide;
}


void AMyCharacter::MoveHorizontal(float Axis) //Moves player 100cm in the x-axis if able to
{
	//Check for wall blocking path
	const float Radius = 1.f;
	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult hit;
	bool MovementBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorRightVector()*Axis*100, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);

	
	if(!bIsHiding && !MovementBlocked && abs(Axis)>0)//Player can move -> Moves player
	{
		SetActorLocation(GetActorLocation()+GetActorRightVector()*Axis*100);
		UGameplayStatics::PlaySoundAtLocation(this, StepSound, GetActorLocation());
	}
	if(MovementBlocked && abs(Axis)>0)//Player is blocked-> plays blocksound
	{
		UGameplayStatics::PlaySoundAtLocation(this, WallBumpSound, GetActorLocation() + GetActorRightVector()*Axis*100);
	}

}

void AMyCharacter::MoveVertical(float Axis) //Moves player 100cm in the y-axis if able to
{
	//Check for wall blocking path
	const float Radius = 1.f;
	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult hit;
	bool MovementBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorForwardVector()*Axis*100, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);

	
	if(!bIsHiding && !MovementBlocked && !bIsMoving && abs(Axis)>0)//Player can move -> Moves player
	{
		SetActorLocation(GetActorLocation()+GetActorForwardVector()*Axis*100);
		UGameplayStatics::PlaySoundAtLocation(this, StepSound, GetActorLocation());
	}
	
	if(MovementBlocked && abs(Axis)>0)//Player is blocked-> plays blocksound
	{
		UGameplayStatics::PlaySoundAtLocation(this, WallBumpSound, GetActorLocation() + GetActorForwardVector()*Axis*100);
	}

}

void AMyCharacter::CameraYaw(float Axis) //Rotates player 90 degrees if able to
{
	if(!bIsHiding && !bIsMoving)
	{
		TargetRotation = TargetRotation + FRotator(0,90*Axis,0);
		UGameplayStatics::PlaySoundAtLocation(this, TurnSwoosh, GetActorLocation()+GetActorRightVector()*Axis*50);
		bIsMoving = true;
	}

}

