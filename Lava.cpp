// Fill out your copyright notice in the Description page of Project Settings.


#include "Lava.h"

#include "Hero.h"
#include "PaperSpriteComponent.h"

ALava::ALava()
{
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
    RootComponent = MySprite;
}

void ALava::BeginPlay()
{
    Super::BeginPlay();
    MySprite->OnComponentHit.AddDynamic(this, &ALava::OnCollision);
}

void ALava::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALava::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->IsA(AHero::StaticClass()))
    {
        Cast<AHero>(OtherActor)->KillHero();
    }
}
