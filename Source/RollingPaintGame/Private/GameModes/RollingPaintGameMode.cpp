// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/RollingPaintGameMode.h"

#include "Characters/CleanerPawn.h"
#include "Kismet/GameplayStatics.h"


void ARollingPaintGameMode::OnTargetPaint(const ATargetPawn* TargetPawn)
{
	ChangeCleanTargetsCount(false);
	if (Cast<ACleanerPawn>(TargetPawn))
	{
		ChangeCleanersCount(false);
	}
}

void ARollingPaintGameMode::OnTargetCleaned(const ATargetPawn* TargetPawn)
{
	ChangeCleanTargetsCount(true);
	if (Cast<ACleanerPawn>(TargetPawn))
	{
		ChangeCleanersCount(true);
	}
}

void ARollingPaintGameMode::BeginPlay()
{
	Super::BeginPlay();

	CleanersCount = GetAllCleaners();
	OnCleanersCountChanged.Broadcast(CleanersCount);
	CleanTargetsCount = GetAllCleanTargets();

	SetGameInputMode(true);
}

void ARollingPaintGameMode::ChangeCleanersCount(bool bIncrease)
{
	if (bIncrease) CleanersCount++;
	else CleanersCount--;

	OnCleanersCountChanged.Broadcast(CleanersCount);
}

void ARollingPaintGameMode::ChangeCleanTargetsCount(bool bIncrease)
{
	if (bIncrease) CleanTargetsCount++;
	else CleanTargetsCount--;

	if (CleanTargetsCount <= 0)
	{
		OnAllTargetsPainted.Broadcast();
		SetGameInputMode(false);
	}
}

int ARollingPaintGameMode::GetAllCleaners() const
{
	TArray<AActor*> Cleaners;
	UGameplayStatics::GetAllActorsOfClass(this,ACleanerPawn::StaticClass(),Cleaners);

	return Cleaners.Num();
}

int ARollingPaintGameMode::GetAllCleanTargets() const
{
	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(this,ATargetPawn::StaticClass(),Targets);

	return Targets.Num();
}

void ARollingPaintGameMode::SetGameInputMode(bool bEnabled)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this,0);
	if (!PlayerController) return;

	bEnabled ? PlayerController->SetInputMode(FInputModeGameOnly()) : PlayerController->SetInputMode(FInputModeUIOnly());
	
	PlayerController->bShowMouseCursor = !bEnabled;
}
