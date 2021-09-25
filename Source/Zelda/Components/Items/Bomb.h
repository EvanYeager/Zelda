#pragma once

#include "CoreMinimal.h"
#include "Components/Items/Weapon.h"
#include "ThrowableInterface.h"
#include "Bomb.generated.h"

class ABombExplosive;

UCLASS()
class ZELDA_API UBomb : public UWeapon, public IThrowableInterface
{
	GENERATED_BODY()

public:
	UBomb();
	void UseStart() override;
protected:
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	void Equip();
	void Throw();
	void SpawnBomb();
	FVector GetBombHoldPosition();
	
	bool isEquipped;
	TSubclassOf<ABombExplosive> BombMeshClass;
	ABombExplosive* BombMesh;
	
};
