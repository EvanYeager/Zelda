#include "PlayerFocusComponent.h"
#include "ZeldaCharacter.h"
#include "GameFramework/PlayerController.h"


void UPlayerFocusComponent::BeginPlay() 
{
   Super::BeginPlay();
   
   AZeldaCharacter* Player = Cast<AZeldaCharacter>(GetOwner());
   check(Player);
   PlayerController = Cast<APlayerController>(Player->GetController());
   CameraManager = PlayerController->PlayerCameraManager;

}
