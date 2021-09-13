#include "Bomb.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Explosives/BombExplosive.h"

UBomb::UBomb()
{
   ConstructorHelpers::FClassFinder<AActor> BombMesh1(TEXT("/Game/ThirdPersonCPP/Blueprints/BombMesh"));
   if (BombMesh1.Succeeded())
      BombMeshClass = BombMesh1.Class;
}

void UBomb::UseStart() 
{
   if (isEquipped) 
      Throw();
   else Equip();
}

void UBomb::Equip() 
{
   isEquipped = true;

   SpawnBomb();
}

void UBomb::Throw() 
{
   isEquipped = false;
   
   if (BombMesh && BombMesh->Mesh)
   {
      // BombMesh->Mesh->AddImpulseAtLocation(BombMesh->GetVelocity() * 300.0f, BombMesh->GetActorLocation());
      BombMesh->Mesh->AddImpulse(GetOwner()->GetVelocity() * 300.0f);
      UE_LOG(LogTemp, Warning, TEXT("Throwing"));
   }
}

void UBomb::SpawnBomb() 
{
   FVector SpawnLocation = GetOwner()->GetActorLocation();
   SpawnLocation.Z += 100;
   BombMesh = Cast<ABombExplosive>(GetWorld()->SpawnActor(BombMeshClass.Get(), &SpawnLocation));
}
