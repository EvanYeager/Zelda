#pragma once

#include "CoreMinimal.h"
#include "Components/Items/Item.h"
#include "Bow.generated.h"

class AZeldaPlayerController;
class AZeldaCharacter;

UCLASS()
class ZELDA_API UBow : public UItem
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
