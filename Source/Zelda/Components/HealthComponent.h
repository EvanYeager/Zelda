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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() { return Health; }
	/** Adds the change amount to current health. 
	 * Negative values will decrease health while positive values will increase health. 
	 * If health goes to 0, the owner of the health component will be destroyed.
	 * @return health after change
	 */
	float ChangeHealth(float Change);

	/** Sets max health variable.
	 * Also ensures the current health is not over the new max health.
	 */
	void SetMaxHealth(float NewHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.0f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
