// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/TargetPawn.h"
#include "Characters/Components/RollingSphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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

	PrimaryActorTick.bCanEverTick = true;
}

void APlayerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//ARollingPaintGameMode* GameMode = Cast<ARollingPaintGameMode>(UGameplayStatics::GetGameMode(this));
	//GEngine->AddOnScreenDebugMessage(-1,0,FColor::Green,FString::Printf(TEXT("Cleaners: %d | CleanTargets: %d"),GameMode->GetCleanersCount(),GameMode->GetCleanTargetsCount()));
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
		TargetPawn->PaintTarget(CurrentPawnColor,ESTATE_Dirty);
		
		if (PaintEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,PaintEffect,GetActorLocation(),GetActorRotation());
		}
	}
}
