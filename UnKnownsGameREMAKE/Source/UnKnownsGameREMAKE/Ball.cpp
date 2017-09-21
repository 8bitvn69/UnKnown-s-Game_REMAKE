// Truong Dai hoc Bach Khoa Ha Noi :: Vien Toan ung dung va Tin hoc :: Toan-Tin 01 K60 :: 20151366

#include "Ball.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RollTorque = 10000000.f;
	JumpImpulse = 100000.f;

	bHitGround = false;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABall::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABall::MoveRight);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABall::Jump);
}

// Called when actor hit something
void ABall::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) {
	bHitGround = Other->ActorHasTag(FName("Ground"));
}

void ABall::MoveForward(float Val) {
	if (BallMesh != nullptr && Arrow != nullptr) {
		if (bHitGround) {
			FVector ArrowRightVector = Arrow->GetRightVector();
			FVector Torque(ArrowRightVector.X * RollTorque * Val, ArrowRightVector.Y * RollTorque * Val, ArrowRightVector.Z * RollTorque * Val);

			BallMesh->AddTorque(Torque);
		}
	}
}

void ABall::MoveRight(float Val) {
	if (BallMesh != nullptr && Arrow != nullptr) {
		if (bHitGround) {
			FVector ArrowForwardVector = Arrow->GetForwardVector();
			FVector Torque(ArrowForwardVector.X * RollTorque * -Val, ArrowForwardVector.Y * RollTorque * -Val, ArrowForwardVector.Z * RollTorque * -Val);

			BallMesh->AddTorque(Torque);
		}
	}
}

void ABall::Jump() {
	if (BallMesh != nullptr) {
		if (bHitGround) {
			BallMesh->AddImpulse(FVector(0.f, 0.f, JumpImpulse));
			bHitGround = false;
		}
	}
}

void ABall::GetBallMesh(UStaticMeshComponent* BallMesh) {
	this->BallMesh = BallMesh;
}

void ABall::GetArrow(UArrowComponent* Arrow) {
	this->Arrow = Arrow;
}