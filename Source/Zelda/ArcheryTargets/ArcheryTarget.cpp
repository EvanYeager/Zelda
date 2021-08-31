#include "ArcheryTarget.h"
#include "GameModes/ArcheryMinigame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArcheryTarget::AArcheryTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AArcheryMinigame* ArcheryGameMode = Cast<AArcheryMinigame>(UGameplayStatics::GetGameMode(GetWorld()));
	OnDeath.BindUObject(ArcheryGameMode, &AArcheryMinigame::DecrementCounter);

}

// Called when the game starts or when spawned
void AArcheryTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArcheryTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

