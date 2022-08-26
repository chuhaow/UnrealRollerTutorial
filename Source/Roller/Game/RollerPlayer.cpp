// Fill out your copyright notice in the Description page of Project Settings.


#include "Roller/Game/RollerPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollerPlayer::ARollerPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//Set Root Component to be Mesh
	RootComponent = Mesh;
	//Attach the Spring Arm to the Mesh, Spring will now follow the Mesh
	SpringArm->SetupAttachment(Mesh);
	//Attach the Camera to the SpringArm, Camera will now follow the SpringArm
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);

	Mesh->OnComponentHit.AddDynamic(this, &ARollerPlayer::OnHit);
	

}

// Called when the game starts or when spawned
void ARollerPlayer::BeginPlay()
{
	Super::BeginPlay();

	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
	
}



// Called to bind functionality to input
void ARollerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ARollerPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollerPlayer::MoveRight);

	InputComponent->BindAction("Jump", IE_Pressed ,this, &ARollerPlayer::Jump);
}

void ARollerPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollerPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollerPlayer::Jump()
{
	if( JumpCount < MaxJumpCount)
	{
		Mesh->AddImpulse(FVector(0,0,JumpImpulse));
		JumpCount++;
	}
	
}

void ARollerPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	const float HitDir = Hit.Normal.Z;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
		FString::Printf(TEXT("Z Normal: %f"), HitDir));
	if(HitDir > 0)
	{
		JumpCount = 0;
	}
}

