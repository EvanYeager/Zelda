#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELDA_API UItem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItem();

	/** Executed when the use button is pressed down */
	virtual void UseStart();
	/** Executed when the use button is released */
	virtual void UseEnd();
	/* Executed when this weapon gets selected */
	virtual void Select();
	
protected:

private:
	UPROPERTY(EditDefaultsOnly)
	UCameraAnim* CameraAnim;

};
