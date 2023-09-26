// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Characters\TargetPawn.h"

#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATargetPawn::ATargetPawn()
{
	ShapeComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	RootComponent = ShapeComponent;

	PawnMesh->SetupAttachment(RootComponent);
	
	TargetState = EROLE_Clean;
}

void ATargetPawn::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().ClearTimer(MoveTimerHandle);
	GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &ThisClass::MoveRandomDirection, MoveTimerRate,true);
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

void ATargetPawn::MoveRandomDirection()
{
	const FVector MoveLocation = GetActorForwardVector() *
		UKismetMathLibrary::RandomUnitVector().GetSafeNormal2D() * ImpulseStrength;
	
	ShapeComponent->AddImpulse(MoveLocation, NAME_None, true);
}
