#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELDA_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FORCEINLINE float GetHealth() { return Health; }
	/** Adds the change amount to current health. Negative values will decrease health while positive values will increase health. */
	void ChangeHealth(float Change);

	float MaxHealth = Health;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
