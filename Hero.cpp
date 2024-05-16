#include "Hero.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

AHero::AHero()
{
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("HeroBodySprite"));
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HeroBodyCapsule"));
    MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("HeroSpringArm"));
    MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HeroBodyCamera"));
    RootComponent = MyBodyCollider;
    MySprite->SetupAttachment(RootComponent);
    MySpringArm->SetupAttachment(RootComponent);
    MyCamera->SetupAttachment(MySpringArm);
}

void AHero::BeginPlay()
{
    Super::BeginPlay();
    CurrentAnimationState = HeroAnimationState::AS_IDLE;
    OldAnimationState = HeroAnimationState::AS_EMPTY;
    ProcessAnimStateMachine();
}

void AHero::MovePlayerHorizontal(float value)
{
    MyBodyCollider->AddForce(FVector(1, 0, 0) * value * PlayerAcceleration, NAME_None, true);
}

void AHero::BounceHero(float force)
{
    MyBodyCollider->AddImpulse(FVector(0, 0, force));
}

void AHero::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
    ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -PlayerMaxSpeed, PlayerMaxSpeed);
    MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);

    IdentifyAnimState();
    ProcessAnimStateMachine();

    if (GetActorLocation().Z < -1000)
    {
        KillHero();
        return;
    }
}

void AHero::IdentifyAnimState()
{
    OldAnimationState = CurrentAnimationState;
    float CurrentSpeed = MyBodyCollider->GetPhysicsLinearVelocity().X;
    if (CurrentSpeed > 5.0f)
    {
        CurrentAnimationState = HeroAnimationState::AS_WALKING_RIGHT;
    }
    else if (CurrentSpeed < -5.0f)
    {
        CurrentAnimationState = HeroAnimationState::AS_WALKING_LEFT;
    }
    else
    {
        CurrentAnimationState = HeroAnimationState::AS_IDLE;
    }
}

void AHero::ProcessAnimStateMachine()
{
    if (CurrentAnimationState == OldAnimationState)
    {
        return;
    }

    switch (CurrentAnimationState)
    {
    case HeroAnimationState::AS_IDLE:
        MySprite->SetFlipbook(Flipbook_Idle);
        break;
    case HeroAnimationState::AS_WALKING_RIGHT:
        MySprite->SetFlipbook(Flipbook_WalkingRight);
        MySprite->SetRelativeRotation(FRotator(0, 0, 0));
        break;
    case HeroAnimationState::AS_WALKING_LEFT:
        MySprite->SetFlipbook(Flipbook_WalkingRight);
        MySprite->SetRelativeRotation(FRotator(0, 180, 0));
        break;
    case HeroAnimationState::AS_DEAD:
        UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
        break;
    }
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("Horizontal", this, &AHero::MovePlayerHorizontal);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHero::JumpAction);
}

void AHero::KillHero()
{
    UE_LOG(LogTemp, Warning, TEXT("Hero is Dead"));
    CurrentAnimationState = HeroAnimationState::AS_DEAD;
    ProcessAnimStateMachine();
}

void AHero::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->Tags.Contains("Lava"))
    {
        KillHero();
    }
    else if (OtherActor->Tags.Contains("Floor"))
    {
        bIsJumping = false;
    }
}

void AHero::JumpAction()
{
    if (!bIsJumping)
    {
        MyBodyCollider->AddImpulse(FVector(0, 0, 1) * JumpForce);
        bIsJumping = true;
        GetWorldTimerManager().SetTimer(JumpTimerHandle, this, &AHero::ResetJumpFlag, JumpResetDelay, false);
    }
}

void AHero::ResetJumpFlag()
{
    bIsJumping = false;
}
