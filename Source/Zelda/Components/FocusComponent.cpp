#include "FocusComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UFocusComponent::UFocusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFocusComponent::FocusStart()
{
	if (Target)
		IsFocusing = true;
	else
	{
		// TODO maybe change this to keep the player's rotation the entire time shift is held down
		FRotator NewPlayerRotation = FRotator(Owner->GetActorRotation().Pitch,
			CameraRotation.Yaw, 
			Owner->GetActorRotation().Roll);
		Owner->SetActorRotation(NewPlayerRotation);
	}
}

void UFocusComponent::FocusEnd()
{
	IsFocusing = false;
}

void UFocusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
	if (IsFocusing)
		Focus();
}

// Called when the game starts 
void UFocusComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AZeldaCharacter>(GetOwner());
	PlayerController = Cast<APlayerController>(Owner->GetController());

	check(Owner);
	check(PlayerController);

	GetWorld()->GetTimerManager().SetTimer(SearchTimerHandle, this, &UFocusComponent::Search, 0.1f, true, 0);
}

void UFocusComponent::Search()
{
	GetCameraViewPoint();
	FHitResult Hit;
	FVector End = CameraLocation + CameraRotation.Vector() * GetSearchRange();
	FQuat quat = FQuat();
	FCollisionQueryParams Params;
	FCollisionResponseParams MoreParams;

	if (GetWorld()->SweepSingleByChannel(Hit, CameraLocation, End, quat, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(TraceSphereRadius), Params, MoreParams))
		Target = Hit.GetActor();
	else
		Target = nullptr;
}

void UFocusComponent::Focus()
{
	if (!Target) return;

	// point camera at target
	GetCameraViewPoint();
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, Target->GetActorLocation()); // find look at rotation
	SetCameraRotation(LookAtRotation);
}

float UFocusComponent::GetSearchRange()
{
	return FocusRange + Owner->GetCameraBoom()->TargetArmLength;
}

void UFocusComponent::GetCameraViewPoint() 
{
	Owner->GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
}

void UFocusComponent::SetCameraRotation(FRotator Rotation) 
{
	Owner->GetController()->SetControlRotation(Rotation);
}
