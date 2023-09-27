// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CleanersCounterWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class ROLLINGPAINTGAME_API UCleanersCounterWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void CleanersCountChanged(int NewCleanersCount);
private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CleanersTextBlock;
};
