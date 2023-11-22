// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoor.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AExitDoor::AExitDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	ExitDoor = CreateDefaultSubobject<USkeletalMeshActorComponent>(TEXT("Mesh"));
	RootComponent = ExitDoor;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(1.000000, 0.700000, 2.500000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<USkeletalMeshActor> SM_ExitDoor
	(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Models/SM_ExitDoor.SM_ExitDoor'"));
	if (SM_ExitDoor.Succeeded()) {
		ExitDoor->SetSkeletalMeshActor(SM_ExitDoor.Object);
	}
	ExitDoor->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}

void AExitDoor::CurFloor(int levelname)
{
	switch (levelname) 
	{
	case B2:
		NextFloor = 1;
		break;
	case B1:
		NextFloor = 2;
		break;
	case floor:
		NextFloor = 3;
		break;
	default:
		;
	}
}
