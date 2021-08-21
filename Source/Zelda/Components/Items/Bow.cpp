#include "Bow.h"
#include "Controllers/ZeldaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "EnemyParent.h"

UBow::UBow() 
{
   static ConstructorHelpers::FClassFinder<UUserWidget> WidgetObj(TEXT("/Game/ThirdPersonCPP/UI/Bow"));
   if (WidgetObj.Succeeded()) {
      WidgetClass = WidgetObj.Class;
   }
}


void UBow::UseStart() 
{
   Controller = Cast<AZeldaPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!Controller) return;

	Controller->ShowWidget(WidgetClass);

	// playercameramanager -> move camera
	// maybe the bow should have the camera movement properties?
	// Controller->PlayerCameraManager->playCameraanim()

}

void UBow::UseEnd() 
{
   if (!Controller) return; // hopefully the UseStart() will always execute before this so it shouldn't be null

   Controller->RemoveActiveWidget();

   Shoot();
}

void UBow::Shoot() 
{
	FHitResult Hit;
   FRotator Rotation = Controller->PlayerCameraManager->GetCameraRotation();
   FVector Start = Controller->PlayerCameraManager->GetCameraLocation();
	FVector End = Start + Rotation.Vector() * RANGE;
	FCollisionQueryParams Params;
	FCollisionResponseParams MoreParams;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params, MoreParams))
   {
      AEnemyParent* HitEnemy = Cast<AEnemyParent>(Hit.GetActor());
      // if (HitEnemy)
         // HitEnemy->TakeDamage(50);
   }   
}

