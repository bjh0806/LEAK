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
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* ForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* RightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* SightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* PauseAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InventoryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* InteractionAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MouseToggleAction;

	void Forward(const FInputActionValue& Value);
	void Right(const FInputActionValue& Value);
	void Sight(const FInputActionValue& Value);
	void Pause(const FInputActionValue& Value);
	void Inventory(const FInputActionValue& Value);
	void Interaction(const FInputActionValue& Value);
	void MouseToggle(const FInputActionValue& Value);

	vector<float> pos{};
	float hp{};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
		float CameraRotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
		float Hp = 100;
};
