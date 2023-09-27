// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollingPaintGameMode.generated.h"

class ATargetPawn;

DECLARE_MULTICAST_DELEGATE_OneParam(FCleanersCountChanged,/*NewCleanersCount*/int);
DECLARE_MULTICAST_DELEGATE(FAllTargetsPainted);

UCLASS()
class ROLLINGPAINTGAME_API ARollingPaintGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	int GetCleanTargetsCount() const {return CleanTargetsCount;}
	int GetCleanersCount() const {return CleanersCount;}
    
	void OnTargetPaint(const ATargetPawn* TargetPawn);
	void OnTargetCleaned(const ATargetPawn* TargetPawn);

	FCleanersCountChanged& GetCleanersCountChangedDelegate() {return OnCleanersCountChanged;}
	FAllTargetsPainted& GetAllTargetsPaintedDelegate() {return OnAllTargetsPainted;}

protected:
	virtual void BeginPlay() override;

	void ChangeCleanersCount(bool bIncrease);
	void ChangeCleanTargetsCount(bool bIncrease);

private:
	int CleanTargetsCount;
	int CleanersCount;
    	
	int GetAllCleaners() const;
	int GetAllCleanTargets() const;

	void SetGameInputMode(bool bEnabled);
	
	FCleanersCountChanged OnCleanersCountChanged;
	FAllTargetsPainted OnAllTargetsPainted;
};
