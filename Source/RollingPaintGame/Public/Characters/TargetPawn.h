// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePawn.h"
#include "TargetPawn.generated.h"

class UPawnAIComponent;
/**
 * 
 */
UCLASS()
class ROLLINGPAINTGAME_API ATargetPawn : public ABasePawn
{
	GENERATED_BODY()
public:
	ATargetPawn();
	
	ETargetState GetTargetState() const {return  TargetState;}
	void SetTargetState(ETargetState NewState);

	void PaintTarget(FColor NewColor, ETargetState NewTargetState);
protected:
	virtual void OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Transient) TEnumAsByte<ETargetState> TargetState;

	UPROPERTY(EditDefaultsOnly,Category="Sound")
	USoundBase* PaintingSound;
	
	void Painted();
	void Cleaned();
private:
	UPROPERTY(EditDefaultsOnly,Category="Components")
	TObjectPtr<UPawnAIComponent> SimpleAiComponent;
};
