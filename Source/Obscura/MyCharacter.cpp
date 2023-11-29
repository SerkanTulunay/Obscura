// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundCue.h"
#include "Door.h"

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
	SpawnPoint = GetActorLocation();
	
	SavePath = FPaths::ProjectDir() + TEXT("Logs/PlayTestLog.json");
	LogEvent("Started Playing");
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ScanHidePlace();
	SetActorRotation(FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime, 500.f ));
	
	if(GetActorRotation().Equals(TargetRotation))//Enables movement if rotation is finished
		bIsMoving = false;

	if(StunTimer >= 0)
		StunTimer-=DeltaTime;
	if(StunTimer>StunCooldown)
		StunTimer=StunCooldown;
	else if(!StunAvailable)
	{
		StunAvailable = true;
		UGameplayStatics::PlaySoundAtLocation(this, StunAvailableSound, GetActorLocation());
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Hide",IE_Pressed,this,&AMyCharacter::ToggleHide);
	PlayerInputComponent->BindAction("Stun", IE_Pressed, this, &AMyCharacter::StunEnemy);
	PlayerInputComponent->BindAction("Pulse",IE_Pressed,this,&AMyCharacter::StartPulse);
	//Old inputs:
	//PlayerInputComponent->BindAxis("Horizontal",this,&AMyCharacter::MoveHorizontal);
	//PlayerInputComponent->BindAxis("Vertical",this,&AMyCharacter::MoveVertical);
	//PlayerInputComponent->BindAxis("MouseYaw",this,&AMyCharacter::CameraYaw);
}

void AMyCharacter::Respawn()
{
	LogEvent("Player Died");
	SetActorLocation(SpawnPoint);
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

void AMyCharacter::StartPulse()
{
	bSendPulse = true;
}

void AMyCharacter::MoveHorizontal(float Axis) //Moves player 100cm in the x-axis if able to
{
	//Check for wall blocking path
	const float Radius = 1.f;
	ECollisionChannel TraceChanel=ECC_Pawn;	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult hit;
	bool MovementBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorRightVector()*Axis*200, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);

	
	if(!bIsHiding && !MovementBlocked && abs(Axis)>0)//Player can move -> Moves player
	{
		SetActorLocation(GetActorLocation()+GetActorRightVector()*Axis*200);
		UGameplayStatics::PlaySoundAtLocation(this, StepSound, GetActorLocation());
		//Sound for being next to wall
		bool FrontBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorForwardVector()*200, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);
		if(FrontBlocked)
			UGameplayStatics::SpawnSoundAttached(WallScratch, GetRootComponent(), NAME_None, GetActorRightVector()*500, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, 1.1, 1, 0, nullptr, nullptr, true);



		bool BackBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorForwardVector()*-200, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);
		if(BackBlocked)
			UGameplayStatics::SpawnSoundAttached(WallScratch, GetRootComponent(), NAME_None, GetActorRightVector()*-500, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, .6, 1, 0, nullptr, nullptr, true);
	}
	if(MovementBlocked && abs(Axis)>0)//Player is blocked-> plays blocksound
	{
		float VolMult;
		if (Axis>0)
			VolMult = 1;
		else
		{
			VolMult = 0.4f;
		}
		if (ADoor* Door = Cast<ADoor>(hit.GetActor()))
		{
			if(Door->bIsLocked)
			{
				if(bHasKey)
				{
					if(Door->bIsFuseDoor)
					{
						//Player just door opening sound
					}
					else
					{
						UGameplayStatics::PlaySoundAtLocation(this,DoorUnlocking,GetActorLocation(),VolMult);
					}
					SetActorLocation(Door->TeleportLocationMesh->GetComponentLocation());
					SpawnPoint  = Door->TeleportLocationMesh->GetComponentLocation();
					bHasKey = false;
					Door->ToggleActiveEnemies();
					LogEvent("Went to next room");
				}
				else
				{
						UGameplayStatics::PlaySoundAtLocation(this, DoorBumpSound, GetActorLocation(), VolMult);
				}
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(this,DoorOpening,GetActorLocation(),VolMult);
				SetActorLocation(Door->TeleportLocationMesh->GetComponentLocation());
				SpawnPoint  = Door->TeleportLocationMesh->GetComponentLocation();
				Door->ToggleActiveEnemies();
				LogEvent("Went to next room");
			}
			
		}
		else
		{
		UGameplayStatics::PlaySoundAtLocation(this, WallBumpSound, GetActorLocation() + GetActorRightVector()*Axis*100);
		}
		UE_LOG(LogTemp,Warning,TEXT("%s"),*hit.GetActor()->GetName());
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
	bool MovementBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorForwardVector()*Axis*200, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);

	
	if(!bIsHiding && !MovementBlocked && !bIsMoving && abs(Axis)>0)//Player can move -> Moves player
	{
		SetActorLocation(GetActorLocation()+GetActorForwardVector()*Axis*200);

		UGameplayStatics::PlaySoundAtLocation(this, StepSound, GetActorLocation());

		//Near wall Sound
		bool RightBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorRightVector()*200, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);
		if(RightBlocked)
			UGameplayStatics::SpawnSoundAttached(WallScratch, GetRootComponent(), NAME_None, GetActorForwardVector()*-500, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, .7, 1, 0, nullptr, nullptr, true);

		bool LeftBlocked = GetWorld()->SweepSingleByChannel(hit, this->GetActorLocation(), this->GetActorLocation()+GetActorRightVector()*-200, FQuat::Identity, TraceChanel, FCollisionShape::MakeSphere(Radius), TraceParams);
		if(LeftBlocked)
			UGameplayStatics::SpawnSoundAttached(WallScratch, GetRootComponent(), NAME_None, GetActorForwardVector()*+500, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false, .7, 1, 0, nullptr, nullptr, true);

		
	}
	
	if(MovementBlocked && abs(Axis)>0)//Player is blocked-> plays blocksound
	{
		float VolMult;
		if (Axis>0)
			VolMult = 1;
		else
		{
			VolMult = 0.4f;
		}
		if (ADoor* Door = Cast<ADoor>(hit.GetActor()))
		{
			if(Door->bIsLocked)
			{
				if(bHasKey)
				{
					if(Door->bIsFuseDoor)
					{
						//Player just door opening sound
					}
					else
					{
						UGameplayStatics::PlaySoundAtLocation(this,DoorUnlocking,GetActorLocation(),VolMult);
					}
					SetActorLocation(Door->TeleportLocationMesh->GetComponentLocation());
					SpawnPoint  = Door->TeleportLocationMesh->GetComponentLocation();
					bHasKey = false;
					Door->ToggleActiveEnemies();
					//LogEvent("Went to next room");
				}
				else
				{
					UGameplayStatics::PlaySoundAtLocation(this, DoorBumpSound, GetActorLocation(), VolMult);
				}
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(this,DoorOpening,GetActorLocation(),VolMult);
				SetActorLocation(Door->TeleportLocationMesh->GetComponentLocation());
				SpawnPoint  = Door->TeleportLocationMesh->GetComponentLocation();
				Door->ToggleActiveEnemies();
				LogEvent("Went to next room");
			}
		}
		else
		{
		UGameplayStatics::PlaySoundAtLocation(this, WallBumpSound, GetActorLocation(), VolMult);
		}
	}
}

void AMyCharacter::StunEnemy()
{
	if (StunTimer<=0)
	{
	StunAvailable = false;

	const float Radius = 500.f;
	UGameplayStatics::PlaySoundAtLocation(this, StunActivation, GetActorLocation());
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	FHitResult EnemyHit;

	bool bhit  = GetWorld()->SweepSingleByChannel(EnemyHit, this->GetActorLocation(), this->GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeSphere(Radius), TraceParams);

	if (bhit)
	{
		if(ARunningEnemy* Enemy = Cast<ARunningEnemy>(EnemyHit.GetActor()))
		{
			Enemy->BecomeStunned();
		}
		LogEvent("Stunned Enemy");
	}
	StunTimer = StunCooldown;
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

void AMyCharacter::LogEvent(const FString& EventName)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FFileHelper::LoadFileToString(ExistingLogData, *SavePath))
	{
		// Existing log data is loaded into ExistingLogData
	}
	
	JsonObject->SetStringField(TEXT("time"), FDateTime::Now().ToString());
	JsonObject->SetStringField(TEXT("Event"), EventName);
	

	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	FString CombinedLogData = ExistingLogData + JsonString + TEXT("\n");
	FFileHelper::SaveStringToFile(CombinedLogData, *SavePath);
}

