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

	/* Get BallMesh and Arrow references from Blueprint */
	// TODO remove later
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void GetBallMesh(class UStaticMeshComponent* BallMesh);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void GetArrow(class UArrowComponent* Arrow);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RollTorque;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float JumpImpulse;

	// Contain references of components
	UStaticMeshComponent* BallMesh = nullptr;
	UArrowComponent* Arrow = nullptr;

private:
	bool bHitGround; // Is the Ball on the ground?
	
};
