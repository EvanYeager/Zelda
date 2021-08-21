#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ZeldaCameraManager.generated.h"

UCLASS()
class ZELDA_API AZeldaCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	void PlayCameraAnimation(UCameraAnim* Anim);
};
