// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UENUM(BlueprintType)
enum ETargetState
{
	EROLE_Clean  UMETA(DisplayName = "CleanPawn"),
	EROLE_Dirty  UMETA(DisplayName = "DirtyPawn"),
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
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	FColor DefaultPawnColor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	FColor CurrentPawnColor;
	
	UPROPERTY()
	UMaterialInstanceDynamic* MeshDynamicMaterial;
	
};
