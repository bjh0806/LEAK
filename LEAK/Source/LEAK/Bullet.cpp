// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Bullet;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(1.000000, 1.000000, 0.700000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Bullet
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/SM_Bullet.SM_Bullet'"));
	if (SM_Bullet.Succeeded()) {
		Bullet->SetStaticMesh(SM_Bullet.Object);
	}
	Bullet->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}
