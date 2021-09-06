#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyParent.h"
#include "Controllers/ZeldaPlayerController.h"

float UWeapon::DamageActor(AEnemyParent* Target) 
{
   FDamageEvent DamageEvent = FDamageEvent();
   AZeldaPlayerController* Controller = Cast<AZeldaPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
   return Target->TakeDamage(CalculateDamage(), DamageEvent, Controller, GetOwner());
}

float UWeapon::CalculateDamage() 
{
   return GrossDamage;
}
