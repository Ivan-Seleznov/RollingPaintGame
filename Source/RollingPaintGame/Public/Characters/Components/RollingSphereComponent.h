// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "RollingSphereComponent.generated.h"

class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROLLINGPAINTGAME_API URollingSphereComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void InitializePlayerInput(UEnhancedInputComponent* InputComponent);

protected:
	UPROPERTY(EditDefaultsOnly,Category="Input") UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly,Category="Input") UInputAction* LookInputAction;
	UPROPERTY(EditDefaultsOnly,Category="Input") UInputAction* MoveInputAction;
	
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly,Category="Movement")
	float RollingSphereMovementSpeed = 530.f;
};
