// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyParent.h"
#include "ArcheryTarget.generated.h"

UCLASS()
class ZELDA_API AArcheryTarget : public AEnemyParent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArcheryTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
