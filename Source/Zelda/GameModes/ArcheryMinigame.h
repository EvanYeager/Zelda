#pragma once

#include "CoreMinimal.h"
#include "ZeldaGameMode.h"
#include "EnemyParent.h"
#include "ArcheryTargets/ArcheryTarget.h"
#include "ArcheryMinigame.generated.h"

class UUserWidget;
class AArcheryTarget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnd);

UENUM(BlueprintType)
enum class Difficulty : uint8
{
	Easy UMETA(DisplayName="Easy"),
	Medium UMETA(DisplayName = "Medium"),
	Hard UMETA(DisplayName = "Hard")
};

USTRUCT(BlueprintType)
struct FClassesToSpawn
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AArcheryTarget> EasyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AArcheryTarget> MediumClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AArcheryTarget> HardClass;
};

UCLASS()
class ZELDA_API UArcheryTargetSpawner : public UActorComponent
{
	GENERATED_BODY()
public:
	UArcheryTargetSpawner();
	void SpawnTargets();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	Difficulty GameDifficulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FVector, Difficulty> SpawnLocations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FClassesToSpawn Classes;
protected:
private:
	/**
	 * Removes targets that are above the selected difficulty. Runs at the start of SpawnTargets().
	 */ 
	void FilterTargets();
};

UCLASS(BlueprintType, Blueprintable)
class ZELDA_API AArcheryMinigame : public AZeldaGameMode
{
	GENERATED_BODY()

public:
	AArcheryMinigame();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int TargetsLeft;

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FOnGameEnd OnEnd;

	UFUNCTION()
	void DecrementCounter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UArcheryTargetSpawner* Spawner;
private:
	TSubclassOf<UUserWidget> MinigameWidget;

	void EndGame();
	
};
