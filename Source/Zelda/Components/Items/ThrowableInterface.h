#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ThrowableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UThrowableInterface : public UInterface
{
	GENERATED_BODY()
};

class ZELDA_API IThrowableInterface
{
	GENERATED_BODY()

public:
	virtual void Throw() = 0;
};
