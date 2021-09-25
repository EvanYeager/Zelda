#include "FocusComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UFocusComponent::UFocusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UFocusComponent::ShouldFocus() 
{
	return true;
}

// Called when the game starts 
void UFocusComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SearchTimerHandle, this, &UFocusComponent::Search, 0.1f, true, 0);
}

void UFocusComponent::Search() {}

void UFocusComponent::FocusStart() 
{
	if (GetOwner()->Implements<UBlockInterface>())
		Cast<IBlockInterface>(GetOwner())->Block();
}

void UFocusComponent::FocusEnd()
{
	if (GetOwner()->Implements<UBlockInterface>())
		Cast<IBlockInterface>(GetOwner())->UnBlock();
}

void UFocusComponent::Focus() {}

void UFocusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
	if (ShouldFocus())
		Focus();
}

float UFocusComponent::GetSearchRange() 
{
	return FocusRange;
}

