#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZeldaPlayerController.generated.h"

class AZeldaCharacter;
class UUserWidget;

UCLASS()
class ZELDA_API AZeldaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AZeldaPlayerController();

	void ShowWidget(TSubclassOf<UUserWidget> Widget);
	void RemoveActiveWidget();

protected:
	virtual void SetupInputComponent() override;

private:
	AZeldaCharacter* Character;

	UUserWidget* ActiveWidget;
	
	UPROPERTY(EditAnywhere)
	UCameraAnim* CameraAnim;

	/**
	 * Intermediary input functions
	 */
	void Jump();
	void StopJumping();
	void ZoomIn();
	void ZoomOut();
	void UseItemStart();
	void UseItemEnd();
	void FocusStart();
	void FocusEnd();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void AddControllerYawInput(float Value);
	void AddControllerPitchInput(float Value);

};
