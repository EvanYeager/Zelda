#pragma once

#include "CoreMinimal.h"
#include "Components/FocusComponent.h"
#include "PlayerFocusComponent.generated.h"

UCLASS()
class ZELDA_API UPlayerFocusComponent : public UFocusComponent
{
	GENERATED_BODY()

public:

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	APlayerController *PlayerController;
	APlayerCameraManager *CameraManager;
	
};
