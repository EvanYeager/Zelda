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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// Timer handle for searching for target via trace
	FTimerHandle SearchTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// TODO move this block to the component owner
	float FocusRange = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// radius of the sphere for searching for targets. Larger radius means targets will be found further from the middle of the camera POV
	float TraceSphereRadius = 300.0f;

	virtual bool ShouldFocus();

	UFUNCTION()
	/** For NPCs, this is called when focusing starts. 
	 * For the player, this is called when the focus button is pressed down. */
	virtual void FocusStart();
	UFUNCTION()
	/** For NPCs, this is called when focusing ends. 
	 * For the player, this is called when the focus button is let go. */
	virtual void FocusEnd();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** The focusable target that is found from a line trace. May be null. */ 
	AActor *Target;

	/** Search (line trace) for target. */
	virtual void Search();
	virtual void Focus();

	virtual float GetSearchRange();
	

private:
};
