// Fill out your copyright notice in the Description page of Project Settings.


#include "Knife.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

AKnife::AKnife()
{
	PrimaryActorTick.bCanEverTick = true;

	Knife = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Knife;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(1.262191, 0.846215, 0.765540));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Knife
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_Knife.SM_Knife'"));
	if (SM_Knife.Succeeded()) {
		Knife->SetStaticMesh(SM_Knife.Object);
	}
	Knife->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
