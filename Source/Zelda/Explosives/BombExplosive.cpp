#include "BombExplosive.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h" 	
#include "ZeldaCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABombExplosive::ABombExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetupAttachment(RootComponent);
	// find and apply mesh asset

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(*MeshAssetPath);
	if (!MeshAsset.Object) return;
	Mesh->SetStaticMesh(MeshAsset.Object);

	// mesh properties
	// Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(false);
	Mesh->RelativeScale3D = FVector(0.5f);
	// Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	// Mesh->SetMassOverrideInKg(TEXT("Static Mesh"), 10.0f);
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

}


void ABombExplosive::SetExplosionTimer(float Delay) 
{
	GetWorld()->GetTimerManager().SetTimer(ExplosionTimer, this, &IExplosive::Explode, Delay, false, Delay);
}

void ABombExplosive::Explode() 
{
	FHitResult Hit;
	TArray<TEnumAsByte<EObjectTypeQuery>> Objects = {EObjectTypeQuery::ObjectTypeQuery3};
	if (UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + 1,
		ExplosionRadius,
		/**
		 * 
		 * ?????????????????????????????????????????????
		 * 
		 */
		ETraceTypeQuery::TraceTypeQuery14,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::Persistent,
		Hit,
		true
	))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());
		APawn* HitPawn = Cast<APawn>(Hit.GetActor());
		if (HitPawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s takes %f damage"), *HitPawn->GetName(), Damage);
			HitPawn->TakeDamage(Damage, FDamageEvent(), UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
		}
	}

	GetWorld()->DestroyActor(this);
}