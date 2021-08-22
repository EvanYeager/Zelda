#pragma once

#include "CoreMinimal.h"
#include "Components/Items/Weapon.h"
#include "Components/Items/ProjectileInterface.h"
#include "Bow.generated.h"

class AZeldaPlayerController;
class AZeldaCharacter;

UCLASS()
class ZELDA_API UBow : public UWeapon, public IProjectileInterface
{
	GENERATED_BODY()

public:
	UBow();

	void FireProjectile();

private:
	void UseStart() override;
	void UseEnd() override;
	
	const float RANGE = 3000.0f;

	TSubclassOf<UUserWidget> WidgetClass;
	AZeldaPlayerController* Controller;
};
