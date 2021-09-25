#include "PlayerFocusComponent.h"
#include "ZeldaCharacter.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"



void UPlayerFocusComponent::BeginPlay() 
{
   Super::BeginPlay();

   Player = Cast<AZeldaCharacter>(GetOwner());
   check(Player);
   PlayerController = Cast<APlayerController>(Player->GetController());
   CameraManager = PlayerController->PlayerCameraManager;
}

void UPlayerFocusComponent::FocusStart() 
{
	Super::FocusStart();
	
	IsFocusHeldDown = true;
   
	// if there is no valid target, change player rotation
	if (!Target)
	{
		// TODO maybe change this to keep the player's rotation the entire time shift is held down
		FRotator NewPlayerRotation = FRotator(GetOwner()->GetActorRotation().Pitch,
			CameraManager->GetCameraRotation().Yaw, 
			Player->GetActorRotation().Roll);
		Player->SetActorRotation(NewPlayerRotation);
	}
}

void UPlayerFocusComponent::FocusEnd() 
{
	Super::FocusEnd();

	IsFocusHeldDown = false;
}

bool UPlayerFocusComponent::ShouldFocus() 
{
	return IsFocusHeldDown && Target;
}

void UPlayerFocusComponent::Search() 
{
   FHitResult Hit;
	FVector Start = CameraManager->GetCameraLocation();
	FVector End = Start + CameraManager->GetCameraRotation().Vector() * GetSearchRange();
	FQuat quat = FQuat();
	FCollisionQueryParams Params;
	FCollisionResponseParams MoreParams;

	if (GetWorld()->SweepSingleByChannel(Hit, Start, End, quat, ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(TraceSphereRadius), Params, MoreParams))
		Target = Hit.GetActor();
	else
		Target = nullptr;
}

void UPlayerFocusComponent::Focus() 
{
   if (!Target) return;

	// point camera at target
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraManager->GetCameraLocation(), Target->GetActorLocation());
	SetCameraRotation(LookAtRotation);
}

float UPlayerFocusComponent::GetSearchRange() 
{
	return FocusRange + Player->GetCameraBoom()->TargetArmLength;
}

void UPlayerFocusComponent::SetCameraRotation(FRotator Rotation) 
{
   PlayerController->SetControlRotation(Rotation);
}

