// Fill out your copyright notice in the Description page of Project Settings.


#include "CrowBar.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

ACrowBar::ACrowBar()
{
	PrimaryActorTick.bCanEverTick = true;

	CrowBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = CrowBar;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(2.000000, 2.000000, 0.600000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CrowBar
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_CrowBar.SM_CrowBar'"));
	if (SM_CrowBar.Succeeded()) {
		CrowBar->SetStaticMesh(SM_CrowBar.Object);
	}
	CrowBar->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
