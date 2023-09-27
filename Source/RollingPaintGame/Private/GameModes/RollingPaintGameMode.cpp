// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/RollingPaintGameMode.h"

#include "Characters/CleanerPawn.h"
#include "Kismet/GameplayStatics.h"


void ARollingPaintGameMode::OnTargetPaint(const ATargetPawn* TargetPawn)
{
	CleanTargetsCount--;
	if (Cast<ACleanerPawn>(TargetPawn)) CleanersCount--;
}

void ARollingPaintGameMode::OnTargetCleaned(const ATargetPawn* TargetPawn)
{
	CleanTargetsCount++;
	if (Cast<ACleanerPawn>(TargetPawn)) CleanersCount++;
}

void ARollingPaintGameMode::BeginPlay()
{
	Super::BeginPlay();

	CleanersCount = GetAllCleaners();
	CleanTargetsCount = GetAllCleanTargets();
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