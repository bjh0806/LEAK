// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "iostream"
#include "vector"
#include "ExitDoor.h"
#include "SpiderAI.h"
#include "ZombieAI.h"
#include "BossAI.h"
#include "Lever.h"
#include "NPC.h"

using namespace std;

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicPlayer.generated.h"

UCLASS()
class LEAK_API ABasicPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicPlayer();
	vector<float> GetPos();
	float GetHp();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	vector<float> pos{};
	float hp{};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
