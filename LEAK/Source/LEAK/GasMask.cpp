// Fill out your copyright notice in the Description page of Project Settings.


#include "GasMask.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AGasMask::AGasMask()
{
	PrimaryActorTick.bCanEverTick = true;

	GasMask = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = GasMask;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(2.500000, 2.500000, 2.000000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GasMask
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_GasMask.SM_GasMask'"));
	if (SM_GasMask.Succeeded()) {
		GasMask->SetStaticMesh(SM_GasMask.Object);
	}
	GasMask->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
