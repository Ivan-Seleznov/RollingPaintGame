// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePawn.h"
#include "TargetPawn.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGPAINTGAME_API ATargetPawn : public ABasePawn
{
	GENERATED_BODY()
public:
	ATargetPawn();

	virtual void BeginPlay() override;
	
	ETargetState GetTargetState() const {return  TargetState;}
	void SetTargetState(ETargetState NewState) {TargetState = NewState;}
	
protected:
	virtual void OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY() TEnumAsByte<ETargetState> TargetState;

	UPROPERTY() FTimerHandle MoveTimerHandle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite) float MoveTimerRate = 1.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite) float ImpulseStrength = 1000.f;
private:
	void MoveRandomDirection();
};
