


#include "Collectible.h"

#include "Roller/Game/RollerGameModeBase.h"
#include "Roller/Game/RollerPlayer.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::OverlapBegin);

}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectible::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ARollerPlayer>(OtherActor))
	{
		Collected();
	}
}

void ACollectible::Collected_Implementation()
{
	ARollerGameModeBase* GM = Cast<ARollerGameModeBase>(GetWorld()->GetAuthGameMode());

	if(GM)
	{
		GM->ItemCollected();
	}
}



