// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ZeldaCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controllers/ZeldaPlayerController.h"
#include "GameFramework/SpringArmComponent.h"


class UFocusComponent;
class UItemParent;

AZeldaCharacter::AZeldaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// components
	FocusComponent = CreateDefaultSubobject<UFocusComponent>(TEXT("Focus Component"));
	Items.Add(CreateDefaultSubobject<UItemParent>(TEXT("Test item")));

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

	SelectedItem = Items[0] ? Items[0] : nullptr;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AZeldaCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AZeldaCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &AZeldaCharacter::ZoomOut);

	PlayerInputComponent->BindAction("UseItem", IE_Released, this, &AZeldaCharacter::UseItem);

	PlayerInputComponent->BindAction("Focus", IE_Pressed, FocusComponent, &UFocusComponent::FocusStart);
	PlayerInputComponent->BindAction("Focus", IE_Released, FocusComponent, &UFocusComponent::FocusEnd);

	PlayerInputComponent->BindAxis("MoveForward", this, &AZeldaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AZeldaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AZeldaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AZeldaCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AZeldaCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AZeldaCharacter::TouchStopped);
}

void AZeldaCharacter::UseItem() 
{
	check(SelectedItem);

	SelectedItem->Use();
}

void AZeldaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AZeldaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
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