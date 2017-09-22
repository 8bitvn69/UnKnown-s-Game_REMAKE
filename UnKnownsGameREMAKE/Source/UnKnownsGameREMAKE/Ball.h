// Truong Dai hoc Bach Khoa Ha Noi :: Vien Toan ung dung va Tin hoc :: Toan-Tin 01 K60 :: 20151366

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ball.generated.h"

UCLASS()
class UNKNOWNSGAMEREMAKE_API ABall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// Binded with MoveForward axis input, move the Ball forward and backward
	void MoveForward(float Val);

	// Binded with MoveRight axis input, move the Ball to the right and left
	void MoveRight(float Val);

	// Binded with Jump action input, push the Ball up
	void Jump();

	void Vertical(float Val);

	void Horizontal(float Val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RollTorque;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float JumpImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MinAngle; // Min angle that camera can reach
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MaxAngle; // Max angle that camera can reach

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MouseYSpeed; // Max speed when move camera with mouse Y

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MouseXSpeed; // Max speed when move camera with mouse X

	// Contain references of components
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BallMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* Arrow = nullptr;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* HoldSpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera = nullptr;

private:
	bool bHitGround; // Is the Ball on the ground?

};
