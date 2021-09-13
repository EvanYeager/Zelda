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

private:
	void Equip();
	void Throw();
	void SpawnBomb();
	
	bool isEquipped;
	TSubclassOf<ABombExplosive> BombMeshClass;
	ABombExplosive* BombMesh;
	
};
