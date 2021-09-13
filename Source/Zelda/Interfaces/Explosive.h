#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TimerManager.h"
#include "Explosive.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UExplosive : public UInterface
{
	GENERATED_BODY()
};

class ZELDA_API IExplosive
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// float Lifetime = 3.5f;
	FTimerHandle ExplosionTimer;

	virtual void SetExplosionTimer(float Delay) = 0;
	virtual void Explode() = 0;
};
