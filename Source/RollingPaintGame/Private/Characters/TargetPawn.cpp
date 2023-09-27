// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TargetPawn.h"

#include "Characters/CleanerPawn.h"
#include "Characters/Components/PawnAIComponent.h"
#include "Components/BoxComponent.h"
#include "GameModes/RollingPaintGameMode.h"
#include "Kismet/GameplayStatics.h"

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

void ATargetPawn::PaintTarget(FColor NewColor, ETargetState NewTargetState)
{
	SetMeshDynamicMaterialColor(NewColor);
	
	if (NewTargetState == ESTATE_Clean) Cleaned();
	else if (NewTargetState == ESTATE_Dirty) Painted();

	TargetState = NewTargetState;
}

void ATargetPawn::OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnPawnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
	
	ATargetPawn* OtherTargetPawn = Cast<ATargetPawn>(OtherActor);
	if (!OtherTargetPawn || Cast<ACleanerPawn>(OtherTargetPawn)) return;
	
	if (TargetState == ESTATE_Dirty && OtherTargetPawn->TargetState == ESTATE_Clean)
	{
		OtherTargetPawn->PaintTarget(CurrentPawnColor,ESTATE_Dirty);
	}
}

void ATargetPawn::Painted()
{
	UGameplayStatics::PlaySoundAtLocation(this,PaintingSound,GetActorLocation());
	if (ARollingPaintGameMode* GameMode = Cast<ARollingPaintGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnTargetPaint(this);
	}
}

void ATargetPawn::Cleaned()
{
	if (ARollingPaintGameMode* GameMode = Cast<ARollingPaintGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->OnTargetCleaned(this);
	}
}

