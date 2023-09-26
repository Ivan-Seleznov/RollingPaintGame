// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Components/RollingSphereComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/BasePawn.h"
#include "Components/ShapeComponent.h"

void URollingSphereComponent::InitializePlayerInput(UEnhancedInputComponent* InputComponent)
{
	if (!GetOwner() || !InputComponent) return;
	
	const APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if (!PlayerPawn) return;

	const APlayerController* PlayerController = Cast<APlayerController>(PlayerPawn->Controller);
	if (!PlayerController) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!Subsystem) return;

	Subsystem->AddMappingContext(DefaultMappingContext,0);
	
	InputComponent->BindAction(MoveInputAction,ETriggerEvent::Triggered, this, &ThisClass::Move);
	InputComponent->BindAction(LookInputAction,ETriggerEvent::Triggered, this, &ThisClass::Look);
}

void URollingSphereComponent::Look(const FInputActionValue& Value)
{
	ABasePawn* Pawn = Cast<ABasePawn>(GetOwner());
	if (!Pawn) return;

	if (!Pawn->Controller) return;
	
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	Pawn->AddControllerYawInput(LookAxisVector.X);
	Pawn->AddControllerPitchInput(LookAxisVector.Y);
}

void URollingSphereComponent::Move(const FInputActionValue& Value)
{
	ABasePawn* Pawn = Cast<ABasePawn>(GetOwner());
	if (!Pawn) return;

	if (!Pawn->Controller) return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Pawn->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		
	if (MovementVector.X != 0.0f)
	{
		Pawn->GetShapeComponent()->AddForce(RightDirection * RollingSphereMovementSpeed * MovementVector.X, NAME_None,true);
	}
	
	if (MovementVector.Y != 0.0f)
	{
		Pawn->GetShapeComponent()->AddForce(ForwardDirection * RollingSphereMovementSpeed * MovementVector.Y, NAME_None,true);
	}
}
