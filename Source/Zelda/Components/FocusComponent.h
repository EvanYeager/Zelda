#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZeldaCharacter.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "FocusComponent.generated.h"

class USpringArmComponent;
class APlayerController;
class UCameraComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ZELDA_API UFocusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFocusComponent();

	// Timer handle for searching for target via trace
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle SearchTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FocusRange = 1000.0f;
	// radius of the sphere for searching for targets. Larger radius means targets will be found further from the middle of the camera POV
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceSphereRadius = 300.0f;

	/** this boolean will trigger Focus() each frame when true. 
	 * Conditions for being true: Search() finds a target AND "Focus" action event is pressed down */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsFocusing;

	UFUNCTION()
	void FocusStart();
	UFUNCTION()
	void FocusEnd();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	class AZeldaCharacter *Owner;
	APlayerController *PlayerController;
	AActor *Target;

	FVector CameraLocation;
	FRotator CameraRotation;

	void Search();
	void Focus();

	float GetSearchRange();
	void GetCameraViewPoint();
	void SetCameraRotation(FRotator Rotation);
};
