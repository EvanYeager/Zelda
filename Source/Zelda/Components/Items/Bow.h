#pragma once

#include "CoreMinimal.h"
#include "Components/Items/ItemParent.h"
#include "Bow.generated.h"

class AZeldaPlayerController;
class AZeldaCharacter;

UCLASS()
class ZELDA_API UBow : public UItemParent
{
	GENERATED_BODY()

public:
	UBow();

private:
	void UseStart() override;
	void UseEnd() override;
	void Shoot();

	const float RANGE = 3000.0f;

	TSubclassOf<UUserWidget> WidgetClass;
	AZeldaPlayerController* Controller;
};
