// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RollingPaintHUD.h"

#include "Blueprint/UserWidget.h"
#include "GameModes/RollingPaintGameMode.h"
#include "Kismet/GameplayStatics.h"

void ARollingPaintHUD::OnAllTargetsPainted()
{
	VictoryWidget->SetVisibility(ESlateVisibility::Visible);
}

void ARollingPaintHUD::BeginPlay()
{
	Super::BeginPlay();
	if (!GameHUDClass) return;
	
	APlayerController* PlayerController = GetOwningPlayerController();
	GameHUDWidget = CreateWidget(PlayerController, GameHUDClass);
	GameHUDWidget->AddToViewport();

	if (!VictoryWidgetClass) return;
	VictoryWidget = CreateWidget(PlayerController,VictoryWidgetClass);
	VictoryWidget->AddToViewport();

	VictoryWidget->SetVisibility(ESlateVisibility::Collapsed);

	ARollingPaintGameMode* GameMode = Cast<ARollingPaintGameMode>( UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	
	GameMode->GetAllTargetsPaintedDelegate().AddUObject(this,&ThisClass::OnAllTargetsPainted);
}
