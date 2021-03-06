#pragma once

#include "CoreMinimal.h"
#include "Components/Items/Weapon.h"
#include "Components/Items/ProjectileInterface.h"
#include "Bow.generated.h"

class AZeldaPlayerController;
class AZeldaCharacter;
class USoundBase;

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

	void CountDrawTime();
	float DrawTime;
	const float MAX_DRAW_TIME = 2.1f;

	void StartDrawTimer();

	float CalculateDamage() override;

	const float RANGE = 3000.0f;
	USoundBase* BowDrawSound;
	USoundBase* BowFireSound;
	UAudioComponent* BowDrawAudio;
	FTimerHandle BowDrawTimer;
	const float BOW_DRAW_TIMER_DELAY = 0.1f;

	TSubclassOf<UUserWidget> WidgetClass;
	AZeldaPlayerController* Controller;
};
