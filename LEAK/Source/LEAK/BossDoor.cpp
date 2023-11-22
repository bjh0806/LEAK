// Fill out your copyright notice in the Description page of Project Settings.


#include "BossDoor.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

ABossDoor::ABossDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	BossDoor = CreateDefaultSubobject<USkeletalMeshActorComponent>(TEXT("Mesh"));
	RootComponent = BossDoor;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(1.000000, 0.700000, 2.500000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<USkeletalMeshActor> DM_BigDoor
	(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Models/DM_BigDoor.DM_BigDoor'"));
	if (DM_BigDoor.Succeeded()) {
		BossDoor->SetSkeletalMeshActor(DM_BigDoor.Object);
	}
	BossDoor->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
