#include "HealthComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UHealthComponent::ChangeHealth(float Change) 
{
	Health = FMath::Clamp(Health + Change, 0.0f, MaxHealth);
	if (Health == 0.0f)
		GetOwner()->Destroy();
	return Health;
}

void UHealthComponent::SetMaxHealth(float NewHealth) 
{
	MaxHealth = FMath::Clamp<float>(NewHealth, 0.0f, TNumericLimits<float>::Max());
	Health = FMath::Clamp<float>(Health, 0.0f, MaxHealth);
}
