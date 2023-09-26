// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "..\..\..\Public\Characters\TargetPawn.h"
#include "Characters/Player/Components/RollingSphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerPawn::APlayerPawn()
{
	ShapeComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	RootComponent = ShapeComponent;
	
	PawnMesh->SetupAttachment(RootComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	RollingSphereComponent = CreateDefaultSubobject<URollingSphereComponent>("RollingSphereComponent");
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		RollingSphereComponent->InitializePlayerInput(EnhancedInputComponent);
	}
}

void APlayerPawn::OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnPawnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	ATargetPawn* TargetPawn = Cast<ATargetPawn>(OtherActor);
	if (!TargetPawn) return;

	if (TargetPawn->GetTargetState() == ESTATE_Clean)
	{
		TargetPawn->SetMeshDynamicMaterialColor(CurrentPawnColor);
		TargetPawn->SetTargetState(ESTATE_Dirty);
	}
}
