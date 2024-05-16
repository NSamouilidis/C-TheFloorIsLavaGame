

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Hero.h" 
#include "Killer.generated.h"

UCLASS()
class PONG_API AKiller : public APawn
{
    GENERATED_BODY()

public:
    AKiller();

    // Public member function to retrieve MyBodyCollider
    UCapsuleComponent* GetBodyCollider() const { return MyBodyCollider; }

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Declare OnCollision and OnHeadOverlap functions
    UFUNCTION()
    void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION()
    void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected: // Change access level to protected
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UPaperSpriteComponent* MySprite;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UCapsuleComponent* MyBodyCollider;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* LeftTrigger;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* RightTrigger;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* HeadTrigger;

    // Add declaration for BounceForce if needed
    float BounceForce;
};