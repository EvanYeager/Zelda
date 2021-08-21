#include "Item.h"
#include "GameFramework/GameMode.h"
#include "Controllers/ZeldaPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UItem::UItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItem::BeginPlay()
{
	Super::BeginPlay();
}

void UItem::UseStart() {}

void UItem::UseEnd() {}


// Called every frame
void UItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

