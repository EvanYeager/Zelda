#include "Bomb.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Explosives/BombExplosive.h"

UBomb::UBomb()
{
   PrimaryComponentTick.bCanEverTick = true;

   ConstructorHelpers::FClassFinder<AActor> BombMesh1(TEXT("/Game/ThirdPersonCPP/Blueprints/BombMesh"));
   if (BombMesh1.Succeeded())
      BombMeshClass = BombMesh1.Class;
}

void UBomb::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
   if (isEquipped && BombMesh) 
   {
      BombMesh->SetActorLocation(GetBombHoldPosition());
   }
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
   
   if (!BombMesh || !BombMesh->Mesh) return;
   BombMesh->Mesh->SetEnableGravity(true);
   // BombMesh->Mesh->AddImpulseAtLocation(BombMesh->GetVelocity() * 300.0f, BombMesh->GetActorLocation());
   BombMesh->Mesh->AddImpulse(FVector(300.0f) + GetOwner()->GetVelocity());
   UE_LOG(LogTemp, Warning, TEXT("Throwing"));
}

void UBomb::SpawnBomb() 
{
   FVector SpawnLocation = GetBombHoldPosition();
   FTransform SpawnTransform = FTransform(FRotator(0.0f), SpawnLocation, FVector(0.5f));
   BombMesh = GetWorld()->SpawnActor<ABombExplosive>(BombMeshClass, SpawnTransform, FActorSpawnParameters());
}

FVector UBomb::GetBombHoldPosition() 
{
   FVector Location = GetOwner()->GetActorLocation();
   // TODO use variable
   Location.Z += 150.0f;
   return Location;
}
