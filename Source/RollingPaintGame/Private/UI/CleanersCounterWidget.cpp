// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CleanersCounterWidget.h"

#include "Components/TextBlock.h"
#include "GameModes/RollingPaintGameMode.h"
#include "Kismet/GameplayStatics.h"

void UCleanersCounterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ARollingPaintGameMode* GameMode = Cast<ARollingPaintGameMode>( UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;

	CleanersTextBlock->SetText(FText::AsNumber(GameMode->GetCleanersCount()));
	GameMode->GetCleanersCountChangedDelegate().AddUObject(this,&ThisClass::CleanersCountChanged);
}

void UCleanersCounterWidget::CleanersCountChanged(int NewCleanersCount)
{
	CleanersTextBlock->SetText(FText::AsNumber(NewCleanersCount));
}