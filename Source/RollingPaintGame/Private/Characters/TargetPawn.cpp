// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Characters\TargetPawn.h"

#include "Characters/Components/PawnSimpleAiComponent.h"
#include "Components/BoxComponent.h"

ATargetPawn::ATargetPawn()
{
	ShapeComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	RootComponent = ShapeComponent;

	PawnMesh->SetupAttachment(RootComponent);

	SimpleAiComponent = CreateDefaultSubobject<UPawnSimpleAiComponent>("SimpleAIComponent");

	
	TargetState = EROLE_Clean;
}

void ATargetPawn::OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnPawnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	ATargetPawn* OtherTargetPawn = Cast<ATargetPawn>(OtherActor);
	if (!OtherTargetPawn) return;

	if (TargetState == EROLE_Dirty && OtherTargetPawn->GetTargetState() == ETargetState::EROLE_Clean)
	{
		OtherTargetPawn->SetMeshDynamicMaterialColor(GetCurrentPawnColor());
		OtherTargetPawn->SetTargetState(EROLE_Dirty);
	}
}
