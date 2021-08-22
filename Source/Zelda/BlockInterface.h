// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BlockInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBlockInterface : public UInterface
{
	GENERATED_BODY()
};

class ZELDA_API IBlockInterface
{
	GENERATED_BODY()

public:
	virtual void Block() = 0;
	virtual void UnBlock() = 0;
};
