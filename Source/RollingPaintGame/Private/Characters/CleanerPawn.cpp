// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CleanerPawn.h"

void ACleanerPawn::OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ATargetPawn* OtherTargetPawn = Cast<ATargetPawn>(OtherActor);
	if (!OtherTargetPawn) return;
	
	if (OtherTargetPawn->GetTargetState() == ESTATE_Dirty && TargetState == ESTATE_Clean)
	{
		OtherTargetPawn->PaintTarget(OtherTargetPawn->GetDefaultPawnColor(),ESTATE_Clean);
		return;
	}
	Super::OnPawnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
