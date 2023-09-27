// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class ROLLINGPAINTGAME_API UVictoryWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UFUNCTION()
	void OnRestartButtonClicked();
};
