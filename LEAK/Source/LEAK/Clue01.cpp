// Fill out your copyright notice in the Description page of Project Settings.


#include "Clue01.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AClue01::AClue01()
{
	PrimaryActorTick.bCanEverTick = true;

	Clue01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Clue01;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(1.000000, 1.000000, 0.946000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Clue01
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_Clue01.SM_Clue01'"));
	if (SM_Clue01.Succeeded()) {
		Clue01->SetStaticMesh(SM_Clue01.Object);
	}
	Clue01->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
