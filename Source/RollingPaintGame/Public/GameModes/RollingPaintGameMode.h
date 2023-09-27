// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollingPaintGameMode.generated.h"

class ATargetPawn;
/**
 * 
 */
UCLASS()
class ROLLINGPAINTGAME_API ARollingPaintGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	int GetCleanTargetsCount() const {return CleanTargetsCount;}
	int GetCleanersCount() const {return CleanersCount;}
    
	void OnTargetPaint(const ATargetPawn* TargetPawn);
	void OnTargetCleaned(const ATargetPawn* TargetPawn);
protected:
	virtual void BeginPlay() override;
    
private:
	int CleanTargetsCount;
	int CleanersCount;
    	
	int GetAllCleaners() const;
	int GetAllCleanTargets() const;
};
