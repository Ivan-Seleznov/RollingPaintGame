// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/TargetPawn.h"
#include "CleanerPawn.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGPAINTGAME_API ACleanerPawn : public ATargetPawn
{
	GENERATED_BODY()
protected:
	virtual void OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
