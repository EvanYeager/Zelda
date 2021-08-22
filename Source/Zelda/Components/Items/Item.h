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

	virtual void UseStart();
	virtual void UseEnd();
	
protected:

private:
	UPROPERTY(EditDefaultsOnly)
	UCameraAnim* CameraAnim;

};
