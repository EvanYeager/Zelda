// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Explosive.h"
#include "BombExplosive.generated.h"

UCLASS()
class ZELDA_API ABombExplosive : public AActor, public IExplosive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombExplosive();

	virtual void SetExplosionTimer(float Delay) override;
	virtual void Explode() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LIFESPAN = 6.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage = 60.0f;

private:
	// you can change this path if needed
	FString MeshAssetPath = TEXT("/Game/Geometry/Meshes/1M_Cube");

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
