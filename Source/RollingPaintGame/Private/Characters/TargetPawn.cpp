// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Characters\TargetPawn.h"

#include "..\..\Public\Characters\Components\PawnAIComponent.h"
#include "Characters/CleanerPawn.h"
#include "Components/BoxComponent.h"

ATargetPawn::ATargetPawn()
{
	ShapeComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	RootComponent = ShapeComponent;

	PawnMesh->SetupAttachment(RootComponent);

	SimpleAiComponent = CreateDefaultSubobject<UPawnAIComponent>("SimpleAIComponent");

	
	TargetState = ESTATE_Clean;
}

void ATargetPawn::SetTargetState(ETargetState NewState)
{
	TargetState = NewState;
}

void ATargetPawn::OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnPawnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	
	ATargetPawn* OtherTargetPawn = Cast<ATargetPawn>(OtherActor);
	if (!OtherTargetPawn || Cast<ACleanerPawn>(OtherTargetPawn)) return;
	
	if (TargetState == ESTATE_Dirty && OtherTargetPawn->TargetState == ESTATE_Clean)
	{
		OtherTargetPawn->SetMeshDynamicMaterialColor(CurrentPawnColor);
		OtherTargetPawn->TargetState = ESTATE_Dirty;
		
	}
}
