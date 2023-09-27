// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PawnAIComponent.h"

#include "Characters/BasePawn.h"
#include "Components/ShapeComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPawnAIComponent::BeginPlay()
{
	Super::BeginPlay();
	ABasePawn* OwnerPawn = Cast<ABasePawn>(GetOwner());
	if (!OwnerPawn) return;

	OwnerPawn->GetWorldTimerManager().ClearTimer(MoveTimerHandle);
	OwnerPawn->GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &ThisClass::MoveRandomDirection, MoveTimerRate,true);
}

void UPawnAIComponent::MoveRandomDirection()
{
	ABasePawn* OwnerPawn = Cast<ABasePawn>(GetOwner());
	if (!OwnerPawn) return;
	
	const FVector MoveLocation = /*OwnerPawn->GetActorForwardVector() **/
	UKismetMathLibrary::RandomUnitVector().GetSafeNormal2D() * ImpulseStrength;
	
	OwnerPawn->GetShapeComponent()->AddImpulse(MoveLocation, NAME_None, true);
}
