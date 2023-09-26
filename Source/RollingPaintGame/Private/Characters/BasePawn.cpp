// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BasePawn.h"

#include "Components/ShapeComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMeshComponent"));
}

void ABasePawn::SetPawnColor(FColor NewColor)
{
}

void ABasePawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshDynamicMaterial = UMaterialInstanceDynamic::Create(MeshMaterial, nullptr);
	SetMeshDynamicMaterialColor(DefaultPawnColor);
	PawnMesh->SetMaterial(0,MeshDynamicMaterial);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	ShapeComponent->OnComponentHit.AddDynamic(this,&ThisClass::OnPawnHit);
}

void ABasePawn::OnPawnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
}

void ABasePawn::SetMeshDynamicMaterialColor(FColor NewColor)
{
	if (!MeshDynamicMaterial) return;

	MeshDynamicMaterial->SetVectorParameterValue("Color",NewColor);

	CurrentPawnColor = NewColor;
}
