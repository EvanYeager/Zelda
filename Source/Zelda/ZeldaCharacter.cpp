// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ZeldaCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controllers/ZeldaPlayerController.h"
#include "Components/FocusComponent.h"
#include "Components/Items/Bow.h"
#include "Components/Items/Bomb.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/HealthComponent.h"


AZeldaCharacter::AZeldaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);

	// components
	FocusComponent = CreateDefaultSubobject<UFocusComponent>(TEXT("Focus Component"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	// set player controller
	AIControllerClass = AZeldaPlayerController::StaticClass();

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;				// Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;		  // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;										 // Camera does not rotate relative to arm

}

void AZeldaCharacter::BeginPlay() 
{
	Super::BeginPlay();
	Items.Empty(); // so idk why tf it has random data for Items[0] at the start but this gets rid of it
	
	UItem* Item;
	Item = NewObject<UItem>(this, UBow::StaticClass());
	Item->RegisterComponent();
	Items.Add(Item);
	Item = NewObject<UItem>(this, UBomb::StaticClass());
	Item->RegisterComponent();
	Items.Add(Item);
	SelectedItem = Items[0] ? Items[0] : nullptr;
}

void AZeldaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AZeldaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AZeldaCharacter::SwapItem(int8_t RelativeIndex) 
{
	if (!SelectedItem || Items.Find(SelectedItem) == INDEX_NONE) return;

	int32 SelectedItemIndex = Items.Find(SelectedItem);
	int32 NewIndex = SelectedItemIndex + RelativeIndex;
	if (NewIndex < 0) NewIndex = Items.Num() - 1;
	else if (NewIndex > Items.Num() - 1) NewIndex = 0;
	SelectedItem = Items[NewIndex];
	SelectedItem->Select();
}


void AZeldaCharacter::Block() 
{
	bCanBeDamaged = false;
}

void AZeldaCharacter::UnBlock() 
{
	bCanBeDamaged = true;
}

void AZeldaCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AZeldaCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AZeldaCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AZeldaCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AZeldaCharacter::ZoomIn()
{
	// clamp value to make sure it doesn't go past the limits
	float NewLength = FMath::Clamp(GetCameraBoom()->TargetArmLength - ZoomAmount, CameraBoomLengthLowerLimit, CameraBoomLengthUpperLimit); 
	
	GetCameraBoom()->TargetArmLength = NewLength;
}

void AZeldaCharacter::ZoomOut()
{
	// clamp value to make sure it doesn't go past the limits
	float NewLength = FMath::Clamp(GetCameraBoom()->TargetArmLength + ZoomAmount, CameraBoomLengthLowerLimit, CameraBoomLengthUpperLimit); 
	
	GetCameraBoom()->TargetArmLength = NewLength;
}
