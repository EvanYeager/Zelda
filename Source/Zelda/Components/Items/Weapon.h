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
	/**
	 * This is the function used in DamageActor() to calculate the gross damage applied to the target.
	 * By default it returns GrossDamage; you can override this function to create custom damage amount logic
	 */
	virtual float CalculateDamage();
};
