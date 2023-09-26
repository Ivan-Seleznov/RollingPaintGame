// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UENUM(BlueprintType)
enum ETargetState
{
	ESTATE_Dirty		UMETA(DisplayName = "DirtyPawn"),
	ESTATE_Clean		UMETA(DisplayName = "CleanPawn")
};

UCLASS(Abstract)
class ROLLINGPAINTGAME_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UShapeComponent* GetShapeComponent() const { return ShapeComponent;}
	FColor GetDefaultPawnColor() const {return DefaultPawnColor;}
	FColor GetCurrentPawnColor() const {return CurrentPawnColor;}

	void SetDefaultPawnColor(FColor NewColor) {DefaultPawnColor = NewColor;}
	
	void SetPawnColor(FColor NewColor);
	virtual void PostInitializeComponents() override;

	void SetMeshDynamicMaterialColor(FColor NewColor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UShapeComponent> ShapeComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UMaterialInstance* MeshMaterial;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	FColor CurrentPawnColor;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta=(AllowPrivateAccess="true"),Category="Color")
	FColor DefaultPawnColor;
	
	UPROPERTY()
	UMaterialInstanceDynamic* MeshDynamicMaterial;
	
};
