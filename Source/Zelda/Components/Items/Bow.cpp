#include "Bow.h"
#include "Controllers/ZeldaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "EnemyParent.h"
#include "ZeldaCharacter.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

UBow::UBow() 
{
   GrossDamage = 30.0f;
   static ConstructorHelpers::FClassFinder<UUserWidget> WidgetObj(TEXT("/Game/ThirdPersonCPP/UI/Bow"));
   if (WidgetObj.Succeeded())
      WidgetClass = WidgetObj.Class;
   ConstructorHelpers::FObjectFinder<USoundBase> SoundObj1(TEXT("/Game/Sounds/Bow_Fire_Arrow"));
   if (SoundObj1.Succeeded())
      BowFireSound = SoundObj1.Object;
   ConstructorHelpers::FObjectFinder<USoundBase> SoundObj2(TEXT("/Game/Sounds/bow_draw"));
   if (SoundObj2.Succeeded())
      BowDrawSound = SoundObj2.Object;
}

void UBow::UseStart() 
{
   Controller = Cast<AZeldaPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (Controller)
	   Controller->ShowWidget(WidgetClass);

	// playercameramanager -> move camera
	// maybe the bow should have the camera movement properties?
	// Controller->PlayerCameraManager->playCameraanim()

   StartDrawTimer();

   if (BowDrawSound)
      BowDrawAudio = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BowDrawSound, GetOwner()->GetActorLocation());
}

void UBow::UseEnd() 
{
   Controller->RemoveActiveWidget();
   GetWorld()->GetTimerManager().ClearTimer(BowDrawTimer);
   if (BowDrawAudio)
      BowDrawAudio->Stop();

   FireProjectile();
}


void UBow::FireProjectile() 
{
   if (BowFireSound)
      UGameplayStatics::PlaySound2D(GetWorld(), BowFireSound);

   FHitResult Hit;
   FRotator Rotation = Controller->PlayerCameraManager->GetCameraRotation();
   FVector Start = Controller->PlayerCameraManager->GetCameraLocation();
	FVector End = Start + Rotation.Vector() * RANGE;
	FCollisionQueryParams Params;
	FCollisionResponseParams MoreParams;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Params, MoreParams))
   {
      AEnemyParent* HitEnemy = Cast<AEnemyParent>(Hit.GetActor());
      if (HitEnemy)
      {
         DamageActor(HitEnemy);
      }
      // TODO maybe have an arrow impact sound
   }
}

void UBow::StartDrawTimer() 
{
   DrawTime = 0.0f; // reset draw time
   GetWorld()->GetTimerManager().SetTimer(BowDrawTimer, this, &UBow::CountDrawTime, BOW_DRAW_TIMER_DELAY, true, 0);
}


void UBow::CountDrawTime() 
{
   DrawTime = FMath::Clamp<float>(DrawTime + BOW_DRAW_TIMER_DELAY, 0.0f, MAX_DRAW_TIME);
}

float UBow::CalculateDamage() 
{
   return GrossDamage * DrawTime / MAX_DRAW_TIME;
}