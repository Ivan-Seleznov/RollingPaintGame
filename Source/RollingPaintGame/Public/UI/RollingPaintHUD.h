// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RollingPaintHUD.generated.h"

/**
 * 
 */
UCLASS()
class ROLLINGPAINTGAME_API ARollingPaintHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	void OnAllTargetsPainted();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = GameHUD, meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = GameHUD, meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> VictoryWidgetClass;

private:
	UPROPERTY() UUserWidget* GameHUDWidget;
	
	UPROPERTY() UUserWidget* VictoryWidget;
};
