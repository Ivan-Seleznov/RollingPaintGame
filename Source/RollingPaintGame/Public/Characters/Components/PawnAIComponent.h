// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnAIComponent.generated.h"

/*
 Simple AI component for BasePawn
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLINGPAINTGAME_API UPawnAIComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY() FTimerHandle MoveTimerHandle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SimpleAI") float MoveTimerRate = 1.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SimpleAI") float ImpulseStrength = 1000.f;

	void MoveRandomDirection();
};
