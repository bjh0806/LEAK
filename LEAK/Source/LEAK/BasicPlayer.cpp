// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
ABasicPlayer::ABasicPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue(TEXT("/Script/Engine.SoundWave'/Game/Lab/Sound/피격_남성3.피격_남성3'"));
	PlayerHit = propellerCue.Object;

	BasicPlayer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BasicPlayer;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(2.400000, 2.400000, 2.000000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 3.234417));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> Character
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/Character.Character'"));
	if (Character.Succeeded()) {
		BasicPlayer->SetStaticMesh(Character.Object);
	}
	BasicPlayer->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}

vector<float> ABasicPlayer::GetPos()
{
	return pos;
}

float ABasicPlayer::GetHp()
{
	return hp;
}

float ABasicPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (hp <= 0.f)
		return	0.f;

	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ABasicPlayer* player = Cast<ABasicPlayer>(PlayerPawn);

	float distance = CalDistance();

	if (!player->GetHp())
		;
	else
		switch (state)
		{
		case idle:
			if (distance < 500)
				state = 1;
			break;
		case follow:
			if (distance <= 700) {
				state = 2;
				isattack = true;
			}
			else
				state = 0;
			break;
		case attack:
			if (isattack) {
				if (distance > 200) {
					state = 1;
				}
			}
			else {
				if (distance > 30)
					state = 1;
			}

			break;
		default:
			;
		}

	return Damage;
}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

