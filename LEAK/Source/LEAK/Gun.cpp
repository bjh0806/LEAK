// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Gun;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(0.856741, 0.356748, 1.103405));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Gun
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_Gun.SM_Gun'"));
	if (SM_Gun.Succeeded()) {
		Gun->SetStaticMesh(SM_Gun.Object);
	}
	Gun->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
