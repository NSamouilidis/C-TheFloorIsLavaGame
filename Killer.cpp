// Fill out your copyright notice in the Description page of Project Settings.


#include "Killer.h"
#include "Components/CapsuleComponent.h"

AKiller::AKiller()
{
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("My Body"));
    LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Left Detector"));
    RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Right Detector"));
    HeadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Head Detector"));

    RootComponent = MyBodyCollider;
    MySprite->SetupAttachment(RootComponent);
    LeftTrigger->SetupAttachment(RootComponent);
    RightTrigger->SetupAttachment(RootComponent);
    HeadTrigger->SetupAttachment(RootComponent);

    
    MyBodyCollider->SetCollisionProfileName("BlockAll");
    LeftTrigger->SetCollisionProfileName("Trigger");
    RightTrigger->SetCollisionProfileName("Trigger");
    HeadTrigger->SetCollisionProfileName("Trigger");
}

void AKiller::BeginPlay()
{
    Super::BeginPlay();
    MyBodyCollider->OnComponentHit.AddDynamic(this, &AKiller::OnCollision);
    HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &AKiller::OnHeadOverlap);
}

void AKiller::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(AHero::StaticClass()))
    {
        Cast<AHero>(OtherActor)->BounceHero(BounceForce);
    }
}

void AKiller::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    
}

void AKiller::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AKiller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

