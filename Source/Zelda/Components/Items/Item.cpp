#include "Item.h"
#include "GameFramework/GameMode.h"
#include "Controllers/ZeldaPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UItem::UItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UItem::UseStart() {}

void UItem::UseEnd() {}

void UItem::Select() {}
