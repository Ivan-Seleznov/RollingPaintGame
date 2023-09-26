// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CleanerPawn.h"

void ACleanerPawn::OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ATargetPawn* OtherTargetPawn = Cast<ATargetPawn>(OtherActor);
	if (!OtherTargetPawn) return;
	
	if (OtherTargetPawn->GetTargetState() == ESTATE_Dirty && TargetState == ESTATE_Clean)
	{
		OtherTargetPawn->SetMeshDynamicMaterialColor(OtherTargetPawn->GetDefaultPawnColor());
		OtherTargetPawn->SetTargetState(ESTATE_Clean);
	}
	Super::OnPawnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
