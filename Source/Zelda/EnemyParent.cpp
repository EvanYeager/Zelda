#include "EnemyParent.h"
#include "Controllers/ZeldaAIController.h"
#include "Components/HealthComponent.h"
#include "Components/Items/Item.h"

// Sets default values
AEnemyParent::AEnemyParent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	AIControllerClass = AZeldaAIController::StaticClass();
}

// Called when the game starts or when spawned
void AEnemyParent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyParent::Block() 
{
	bCanBeDamaged = false;	
}

void AEnemyParent::UnBlock() 
{
	bCanBeDamaged = true;
}

float AEnemyParent::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) 
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return ShouldTakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser) ? HealthComponent->ChangeHealth(-Damage) : HealthComponent->GetHealth();
}

void AEnemyParent::Destroyed() 
{
	OnDeath.ExecuteIfBound();
}

