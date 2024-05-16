// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Hero.generated.h"

UENUM()
enum class HeroAnimationState : uint8
{
    AS_WALKING_RIGHT,
    AS_WALKING_LEFT,
    AS_IDLE,
    AS_EMPTY,
    AS_DEAD
};

UCLASS()
class PONG_API AHero : public APawn
{
    GENERATED_BODY()

public:
    AHero();

    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UPaperFlipbookComponent* MySprite;

    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UCapsuleComponent* MyBodyCollider;

    UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
    class USpringArmComponent* MySpringArm;

    UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
    class UCameraComponent* MyCamera;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float JumpForce = 4000.0f;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float PlayerAcceleration = 1000.0f;

    UPROPERTY(EditAnywhere, Category = "Player Properties")
    float PlayerMaxSpeed = 32.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_WalkingRight;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    class UPaperFlipbook* Flipbook_Idle;

    UPROPERTY(VisibleAnywhere, Category = "Animations")
    HeroAnimationState CurrentAnimationState;

    UPROPERTY(VisibleAnywhere, Category = "Animations")
    HeroAnimationState OldAnimationState;

    
    void BounceHero(float force);
    void ResetJumpFlag(); 
        FTimerHandle JumpTimerHandle;

    
    UPROPERTY(EditDefaultsOnly, Category = "Jump")
    float JumpResetDelay = 0.5f; 

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void KillHero();

protected:
    bool bIsJumping;
    virtual void BeginPlay() override;

    void MovePlayerHorizontal(float value);
    void JumpAction();
    void IdentifyAnimState();
    void ProcessAnimStateMachine();
    void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);
};

