#include "ArcheryMinigame.h"
#include "EnemyParent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/HealthComponent.h"
#include "Controllers/ZeldaPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Controllers/ZeldaPlayerController.h"
#include "ArcheryTargets/ArcheryTarget.h"


UArcheryTargetSpawner::UArcheryTargetSpawner() 
{
   SpawnLocations.Add(FVector(-680, -370,  560.459839), Difficulty::Easy);
   SpawnLocations.Add(FVector( 950, -510,  490.459839), Difficulty::Easy);
   SpawnLocations.Add(FVector( 480,  310,  400.459839), Difficulty::Easy);
   SpawnLocations.Add(FVector(-100,  950,  320.459839), Difficulty::Easy);
   SpawnLocations.Add(FVector( 480,  1300, 580.459839), Difficulty::Easy);
}

void UArcheryTargetSpawner::SpawnTargets() 
{
   FilterTargets(); // skips over the targets that are above the selected difficulty
   for (auto Target : SpawnLocations)
   {
      FTransform Transform = FTransform(FRotator(0), Target.Key, FVector(1.0f / ((float)(uint8)Target.Value + 1.0f)));
      TSubclassOf<AArcheryTarget> Class;
      switch (Target.Value)
      {
      case Difficulty::Easy:
         Class = Classes.EasyClass;
         break;
      case Difficulty::Medium:
         Class = Classes.MediumClass;
         break;
      case Difficulty::Hard:
         Class = Classes.HardClass;
         break;
      }
      if (!Class) continue;
      AArcheryTarget* TargetSpawned = GetWorld()->SpawnActor<AArcheryTarget>(Class, Transform, FActorSpawnParameters());
      TargetSpawned->HealthComponent->SetMaxHealth(1.0f);
   }
}

void UArcheryTargetSpawner::FilterTargets()
{
   TArray<FVector> TargetsToBeRemoved;
   for (auto Target : SpawnLocations)
      if (Target.Value > GameDifficulty) TargetsToBeRemoved.Add(Target.Key);
   for (FVector TargetKey : TargetsToBeRemoved)
      SpawnLocations.Remove(TargetKey);
}


AArcheryMinigame::AArcheryMinigame() 
{
   Spawner = CreateDefaultSubobject<UArcheryTargetSpawner>(TEXT("Spawner"));

   PlayerControllerClass = AZeldaPlayerController::StaticClass();
   ConstructorHelpers::FClassFinder<UUserWidget> WidgetObj(TEXT("/Game/ThirdPersonCPP/UI/ArcheryMinigame_UI"));
   if (WidgetObj.Succeeded())
      MinigameWidget = WidgetObj.Class;
}


void AArcheryMinigame::BeginPlay() 
{
   Super::BeginPlay();

   Spawner->SpawnTargets();
   TargetsLeft = Spawner->SpawnLocations.Num();

   AZeldaPlayerController* PlayerController = Cast<AZeldaPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
   PlayerController->ShowWidget(MinigameWidget);
}


void AArcheryMinigame::DecrementCounter() 
{
   if (--TargetsLeft < 1)
      EndGame();
}

void AArcheryMinigame::EndGame() 
{
   OnEnd.Broadcast();
}