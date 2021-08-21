#include "ZeldaPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ZeldaCameraManager.h"
#include "ZeldaCharacter.h"
#include "Components/FocusComponent.h"
#include "Components/Items/ItemParent.h"

AZeldaPlayerController::AZeldaPlayerController()
{
   PlayerCameraManagerClass = AZeldaCameraManager::StaticClass();
}


void AZeldaPlayerController::SetupInputComponent() 
{
   Super::SetupInputComponent();

   // Set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &AZeldaPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AZeldaPlayerController::StopJumping);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AZeldaPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AZeldaPlayerController::ZoomOut);

	InputComponent->BindAction("UseItem", IE_Pressed, this, &AZeldaPlayerController::UseItemStart);
	InputComponent->BindAction("UseItem", IE_Released, this, &AZeldaPlayerController::UseItemEnd);

	InputComponent->BindAction("Focus", IE_Pressed, this, &AZeldaPlayerController::FocusStart);
	InputComponent->BindAction("Focus", IE_Released, this, &AZeldaPlayerController::FocusEnd);

	InputComponent->BindAxis("MoveForward", this, &AZeldaPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AZeldaPlayerController::MoveRight);

	InputComponent->BindAxis("Turn", this, &AZeldaPlayerController::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AZeldaPlayerController::AddControllerPitchInput);
}

void AZeldaPlayerController::Jump() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->Jump();
}

void AZeldaPlayerController::StopJumping() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->StopJumping();
}

void AZeldaPlayerController::ZoomIn() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->ZoomIn();
}

void AZeldaPlayerController::ZoomOut() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->ZoomOut();
}

void AZeldaPlayerController::UseItemStart() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character || !Character->SelectedItem) return;
   Character->SelectedItem->UseStart();
}

void AZeldaPlayerController::UseItemEnd() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character || !Character->SelectedItem) return;
   Character->SelectedItem->UseEnd();
}

void AZeldaPlayerController::FocusStart() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->FocusComponent->FocusStart();
}

void AZeldaPlayerController::FocusEnd() 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->FocusComponent->FocusEnd();
}

void AZeldaPlayerController::MoveForward(float Value) 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->MoveForward(Value);
}

void AZeldaPlayerController::MoveRight(float Value) 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->MoveRight(Value);
}

void AZeldaPlayerController::AddControllerYawInput(float Value) 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->AddControllerYawInput(Value);
}

void AZeldaPlayerController::AddControllerPitchInput(float Value) 
{
   Character = Cast<AZeldaCharacter>(GetPawn());
   if (!Character) return;
   Character->AddControllerPitchInput(Value);
}


void AZeldaPlayerController::ShowWidget(TSubclassOf<UUserWidget> Widget) 
{
   if (!Widget) return;
   
   ActiveWidget = CreateWidget(this, Widget);
   ActiveWidget->AddToViewport();
}

void AZeldaPlayerController::RemoveActiveWidget() 
{
   if (!ActiveWidget) return;

   ActiveWidget->RemoveFromParent();
}