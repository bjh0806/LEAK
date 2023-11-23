// Fill out your copyright notice in the Description page of Project Settings.


#include "FileBox_Movable.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AFileBox_Movable::AFileBox_Movable()
{
	PrimaryActorTick.bCanEverTick = true;

	FileBox_Movable = CreateDefaultSubobject<USkeletalMeshActorComponent>(TEXT("Mesh"));
	RootComponent = FileBox_Movable;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(2.000000, 1.700000, 2.000000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<USkeletalMeshActor> DM_FileBox_Movable
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/DM_FileBox_Movable.DM_FileBox_Movable'"));
	if (DM_FileBox_Movable.Succeeded()) {
		FileBox_Movable->SetSkeletalMeshActor(DM_FileBox_Movable.Object);
	}
	FileBox_Movable->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
