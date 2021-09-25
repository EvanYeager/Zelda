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
class APlayerCameraManager;

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

	// TODO move this block to the component owner
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FocusRange = 1000.0f;
	// radius of the sphere for searching for targets. Larger radius means targets will be found further from the middle of the camera POV
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TraceSphereRadius = 300.0f;

	// TODO 
	/** this boolean will trigger Focus() each frame when true. 
	 * Conditions for being true: Search() finds a target AND "Focus" action event is pressed down 
	 */
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

	/** The focusable target that is found from a line trace. May be null. */ 
	AActor *Target;

	/** Search (line trace) for target. */
	void Search();
	void Focus();

	float GetSearchRange();
	void SetCameraRotation(FRotator Rotation);
	
private:
};
