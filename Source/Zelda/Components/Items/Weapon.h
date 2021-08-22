#pragma once

#include "CoreMinimal.h"
#include "Components/Items/Item.h"
#include "Weapon.generated.h"

class AEnemyParent;

UCLASS()
class ZELDA_API UWeapon : public UItem
{
	GENERATED_BODY()

public:

protected:
	float GrossDamage;
	
	float DamageActor(AEnemyParent* Target);
};
