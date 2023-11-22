// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"
#include "Shutter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = true;

	Lever = CreateDefaultSubobject<USkeletalMeshActorComponent>(TEXT("Mesh"));
	RootComponent = Lever;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(0.700000, 0.700000, 1.000000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<USkeletalMeshActor> SM_Lever
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_Lever.SM_Lever'"));
	if (SM_Lever.Succeeded()) {
		Lever->SetSkeletalMeshActor(SM_Lever.Object);
	}
	Lever->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}

void ALever::LeverDown()
{
	AShutter* shutter{};
	shutter->ShutDown();
}
