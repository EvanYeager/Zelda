#pragma once

#include "CoreMinimal.h"
#include "Components/FocusComponent.h"
#include "PlayerFocusComponent.generated.h"

UCLASS()
class ZELDA_API UPlayerFocusComponent : public UFocusComponent
{
	GENERATED_BODY()

public:
	virtual void FocusStart() override;
	virtual void FocusEnd();

	virtual bool ShouldFocus() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Search() override;
	virtual void Focus() override;
	virtual float GetSearchRange() override;

private:
	AZeldaCharacter *Player;
	APlayerController *PlayerController;
	APlayerCameraManager *CameraManager;
	bool IsFocusHeldDown;
	
	virtual void SetCameraRotation(FRotator Rotation);
	
};
