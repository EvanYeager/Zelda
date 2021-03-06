#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BlockInterface.h"
#include "EnemyParent.generated.h"

class UHealthComponent;

UCLASS()
class ZELDA_API AEnemyParent : public APawn, public IBlockInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyParent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	DECLARE_DELEGATE(FOnDeathDelegate);
	FOnDeathDelegate OnDeath;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Block() override;
	virtual void UnBlock() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

private:
	virtual void Destroyed() override;
};
