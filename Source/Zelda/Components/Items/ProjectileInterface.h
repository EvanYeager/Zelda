#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectileInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProjectileInterface : public UInterface
{
	GENERATED_BODY()
};

class ZELDA_API IProjectileInterface
{
	GENERATED_BODY()

public:
	virtual void FireProjectile() = 0;
};
