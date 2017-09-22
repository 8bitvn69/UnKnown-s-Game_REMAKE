// Truong Dai hoc Bach Khoa Ha Noi :: Vien Toan ung dung va Tin hoc :: Toan-Tin 01 K60 :: 20151366

#include "Ball.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"


// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TheBallMesh(TEXT("/Game/_MyWork/StaticMeshes/BallMesh.BallMesh"));

	// Create mesh component for the ball
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Ball Mesh"));
	BallMesh->SetStaticMesh(TheBallMesh.Object);
	BallMesh->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetLinearDamping(0.1f);
	BallMesh->SetAngularDamping(0.1f);
	RootComponent = BallMesh;

	// Create a holder for the spring arm
	HoldSpringArm = CreateDefaultSubobject<USceneComponent>(FName("Hold Spring Arm"));
	HoldSpringArm->AttachToComponent(BallMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Create a spring arm to hold a camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm"));
	SpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	SpringArm->AttachToComponent(HoldSpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	// Create a camera
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	// Create a arrow
	Arrow = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	Arrow->ArrowColor = FColor::Green;
	Arrow->ArrowSize = 1.f;
	Arrow->ScreenSize = 0.0025f;
	Arrow->AttachToComponent(HoldSpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	RollTorque = 10000000.f;
	JumpImpulse = 100000.f;

	MinAngle = -60.f;
	MaxAngle = 0.f;
	MouseYSpeed = 2.f;
	MouseXSpeed = 2.f;

	bHitGround = false;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	// Keep rotation of HoldSpringArm absolute when move the BallMesh
	HoldSpringArm->SetAbsolute(false, true, true);
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
	
	PlayerInputComponent->BindAxis("Vertical", this, &ABall::Vertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &ABall::Horizontal);
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

void ABall::Vertical(float Val) {
	if (SpringArm != nullptr) {
		float Angle = SpringArm->RelativeRotation.Pitch + MouseXSpeed * Val;
		if (Angle > MinAngle && Angle < MaxAngle) {
			SpringArm->SetRelativeRotation(FRotator(Angle, 0.f, 0.f));
		}
		
	}
}

void ABall::Horizontal(float Val) {
	if (HoldSpringArm != nullptr) {
		HoldSpringArm->AddRelativeRotation(FRotator(0.f, MouseYSpeed * Val, 0.f));
	}
}