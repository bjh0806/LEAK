// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#incldue "iostream"
#include "vector"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossAI.generated.h"
using namespace std;

UCLASS()
class LEAK_API ABossAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossAI();

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundWave* BossDeath;

	/*UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* AudioComponent;*/

	vector<float> GetPos();
	float GetHp();
	float CalDistance();
	int GetState();
	void EndAttack();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	vector<float> pos{};
	float hp{};
	enum states {
		idle, follow, attack, death
	};
	int state{ 0 };
	bool isattack{};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
