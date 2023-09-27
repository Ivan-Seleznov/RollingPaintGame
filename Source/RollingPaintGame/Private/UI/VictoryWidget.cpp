// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VictoryWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UVictoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	RestartButton->OnClicked.AddDynamic(this,&ThisClass::OnRestartButtonClicked);
}

void UVictoryWidget::OnRestartButtonClicked()
{
	UGameplayStatics::OpenLevel(this,FName(*UGameplayStatics::GetCurrentLevelName(this)), false);
	SetVisibility(ESlateVisibility::Collapsed);
}
