#pragma once

#include "CoreMinimal.h"
#include "Components/FocusComponent.h"
#include "NPCFocusComponent.generated.h"

UCLASS()
class ZELDA_API UNPCFocusComponent : public UFocusComponent
{
	GENERATED_BODY()

public:
	virtual void FocusStart();

protected:
	virtual bool ShouldFocus() override;

	virtual void Search() override;
	virtual void Focus() override;

private:
	
};
