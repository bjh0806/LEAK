// Fill out your copyright notice in the Description page of Project Settings.


#include "Clue02.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AClue02::AClue02()
{
	PrimaryActorTick.bCanEverTick = true;

	Clue02 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Clue02;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(1.000000, 1.000000, 0.946000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Clue02
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_Clue02.SM_Clue02'"));
	if (SM_Clue02.Succeeded()) {
		Clue02->SetStaticMesh(SM_Clue02.Object);
	}
	Clue02->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
