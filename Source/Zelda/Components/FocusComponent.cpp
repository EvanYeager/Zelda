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

// Called when the game starts 
void UFocusComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AZeldaCharacter>(GetOwner());
	PlayerController = Cast<APlayerController>(Player->GetController());
	CameraManager = PlayerController->PlayerCameraManager;

	check(Player);
	check(PlayerController);
	check(CameraManager);

	GetWorld()->GetTimerManager().SetTimer(SearchTimerHandle, this, &UFocusComponent::Search, 0.1f, true, 0);
}

void UFocusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
	if (IsFocusing)
		Focus();
}

void UFocusComponent::FocusStart()
{
	if (GetOwner()->Implements<UBlockInterface>())
		Cast<IBlockInterface>(GetOwner())->Block();

	if (Target)
		IsFocusing = true;
	else
	{
		// TODO maybe change this to keep the player's rotation the entire time shift is held down
		FRotator NewPlayerRotation = FRotator(Player->GetActorRotation().Pitch,
			CameraManager->GetCameraRotation().Yaw, 
			Player->GetActorRotation().Roll);
		Player->SetActorRotation(NewPlayerRotation);
	}
}

void UFocusComponent::FocusEnd()
{
	if (GetOwner()->Implements<UBlockInterface>())
		Cast<IBlockInterface>(GetOwner())->Block();
	IsFocusing = false;
}

void UFocusComponent::Search()
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

void UFocusComponent::Focus()
{
	if (!Target) return;

	// point camera at target
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CameraManager->GetCameraLocation(), Target->GetActorLocation());
	SetCameraRotation(LookAtRotation);
}

float UFocusComponent::GetSearchRange()
{
	return FocusRange + Player->GetCameraBoom()->TargetArmLength;
}

void UFocusComponent::SetCameraRotation(FRotator Rotation) 
{
	PlayerController->SetControlRotation(Rotation);
}
