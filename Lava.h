// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Lava.generated.h"

UCLASS()
class PONG_API ALava : public AActor
{
    GENERATED_BODY()

public:
    ALava();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UPaperSpriteComponent* MySprite;


protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;



    UFUNCTION()
    void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit); 
};