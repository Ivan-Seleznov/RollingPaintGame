// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS(Abstract)
class ROLLINGPAINTGAME_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UShapeComponent* GetShapeComponent() const { return ShapeComponent;}
	FColor GetDefaultPawnColor() const {return DefaultPawnColor;}

	void SetPawnColor(FColor NewColor);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SetMeshDynamicMaterialColor(const FColor& NewColor);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UShapeComponent> ShapeComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UMaterialInstance* MeshMaterial;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	FColor DefaultPawnColor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	FColor CurrentPawnColor;
	
	UPROPERTY()
	UMaterialInstanceDynamic* MeshDynamicMaterial;
};
