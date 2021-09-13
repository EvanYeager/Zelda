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

	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LIFESPAN = 4.0f;

private:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
