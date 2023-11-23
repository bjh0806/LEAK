// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAI.h"
#include "BasicPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
AZombieAI::AZombieAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue(TEXT("/Script/Engine.SoundWave'/Game/Lab/Sound/Zombie_Idle.Zombie_Idle'"));
	ZombieIdle = propellerCue.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> propellerCue2(TEXT("/Script/Engine.SoundWave'/Game/Semin/Sound/Zombie_Attack.Zombie_Attack'"));
	ZombieAttack = propellerCue2.Object;

	ZombieAI = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = ZombieAI;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(1.300000, 1.000000, 2.300000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 60.275542, 0.f));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> DM_Zombie
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Models/DM_Zombie.DM_Zombie'"));
	if (DM_Zombie.Succeeded()) {
		ZombieAI->SetStaticMesh(DM_Zombie.Object);
	}
	ZombieAI->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}

vector<float> AZombieAI::GetPos()
{
	return pos;
}

float AZombieAI::GetHp()
{
	return hp;
}

int AZombieAI::GetState()
{
	return state;
}

void AZombieAI::EndAttack()
{
	ABasicPlayer* player = Cast<ABasicPlayer>(GetBasicPlayer());;
	if (!player->GetHp())
		;
	else
		if (CalDistance() < 100)
			player->Damage();
	isattack = false;
	if (CalDistance() > 101)
		state = 1;
	else
		isattack = true;
}

float AZombieAI::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
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

float AZombieAI::CalDistance()
{
	ABasicPlayer* player = Cast<ABasicPlayer>(GetBasicPlayer());;
	vector<float> temp = player->GetPos();
	float distance = temp[1] - GetPos()[1];

	return distance;
}


// Called when the game starts or when spawned
void AZombieAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieAI::NotifyActorBeginOverlap(AActor* OtherActor)
{
	FString name = OtherActor->GetName();

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		auto player = UGameplayStatics::GetPlayerCharacter(TheWorld, 0);
		if (Cast<ABasicPlayer>(OtherActor) != player) {
			if (isattack == false) {

				FDamageEvent DamageEvent;
				OtherActor->TakeDamage(Damage, DamageEvent, UGameplayStatics::GetPlayerController(TheWorld, 0), this);

				isattack = true;
			}
		}
	}

}

// Called to bind functionality to input
void AZombieAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

