// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZeldaCharacter.generated.h"

class UFocusComponent;
class UItem;
class UHealthComponent;

/**
 * enum for the different items that affect how input is handled. 
 * For example, mouse input in the "Bow" mode will move the camera differently than in "Normal" mode
 */
UENUM(BlueprintType)
enum class InputMode : uint8
{
	Normal UMETA(DisplayName="Normal"),
	Bow UMETA(DisplayName="Bow")
};

UCLASS(config=Game)
class AZeldaCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AZeldaCharacter();

	/**
	 * Input Functions
	 */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void ZoomIn();
	void ZoomOut();
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float ZoomAmount = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFocusComponent* FocusComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	TArray<UItem*> Items;

	// do I need this?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
	InputMode InputMode;

	UItem* SelectedItem;
	UHealthComponent* HealthComponent;

protected:


private:
	float CameraBoomLengthUpperLimit = 1000.0f;
	float CameraBoomLengthLowerLimit = 300.0f;

protected:


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

