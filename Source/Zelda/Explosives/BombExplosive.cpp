#include "BombExplosive.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABombExplosive::ABombExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	RootComponent = Mesh;
}


// Called when the game starts or when spawned
void ABombExplosive::BeginPlay()
{
	Super::BeginPlay();

	SetExplosionTimer(LIFESPAN);
}

// Called every frame
void ABombExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetActorLocation().ToString());
}


void ABombExplosive::SetExplosionTimer(float Delay) 
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimer, this, &IExplosive::Explode, Delay, false, Delay);
}

void ABombExplosive::Explode() 
{
	GetWorld()->DestroyActor(this);
}