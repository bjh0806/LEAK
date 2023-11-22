// Fill out your copyright notice in the Description page of Project Settings.


#include "GasFilter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AGasFilter::AGasFilter()
{
	PrimaryActorTick.bCanEverTick = true;

	GasFilter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = GasFilter;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(2.342156, 2.342156, 1.500000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Filter
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_Filter.SM_Filter'"));
	if (SM_Filter.Succeeded()) {
		GasFilter->SetStaticMesh(SM_Filter.Object);
	}
	GasFilter->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
