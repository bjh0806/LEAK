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


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraLagSpeed = 20.f;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Forward(TEXT("InputAction'/Game/Lab/KeyInput/IA_Forward.IA_Forward'"));
	if (Input_Forward.Succeeded())
	{
		ForwardAction = Input_Forward.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Right(TEXT("InputAction'/Game/Lab/KeyInput/IA_Right.IA_Right'"));
	if (Input_Right.Succeeded())
	{
		RightAction = Input_Right.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Sight(TEXT("InputAction'/Game/Lab/KeyInput/IA_Sight.IA_Sight'"));
	if (Input_Sight.Succeeded())
	{
		SightAction = Input_Sight.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Jump(TEXT("InputAction'/Game/Lab/KeyInput/IA_Jump.IA_Jump'"));
	if (Input_Jump.Succeeded())
	{
		JumpAction = Input_Jump.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_MouseToggle(TEXT("InputAction'/Game/Semin/KeyInput/IA_MouseToggle.IA_MouseToggle'"));
	if (Input_MouseToggle.Succeeded())
	{
		MouseToggleAction = Input_MouseToggle.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Inventory(TEXT("InputAction'/Game/Lab/KeyInput/IA_Inventory.IA_Inventory'"));
	if (Input_Inventory.Succeeded())
	{
		InventoryAction = Input_Inventory.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Interaction(TEXT("InputAction'/Game/Lab/KeyInput/IA_Interaction.IA_Interaction'"));
	if (Input_Interaction.Succeeded())
	{
		InteractionAction = Input_Interaction.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Pause(TEXT("/Script/EnhancedInput.InputAction'/Game/Lab/KeyInput/IA_Pause.IA_Pause'"));
	if (Input_Pause.Succeeded())
	{
		PauseAction = Input_Pause.Object;
	}


	BasicPlayer = CreateDefaultSubobject<UCharacterComponent>(TEXT("Mesh"));
	RootComponent = BasicPlayer;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetRelativeScale3D(FVector(2.400000, 2.400000, 2.000000));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 3.234417));


	static ConstructorHelpers::FObjectFinder<UCharacter> Character
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

void ABasicPlayer::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
	}

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

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &ABasicPlayer::Forward);
		EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Triggered, this, &ABasicPlayer::Right);
		EnhancedInputComponent->BindAction(SightAction, ETriggerEvent::Triggered, this, &ABasicPlayer::Sight);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABasicPlayer::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABasicPlayer::StopJumping);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ABasicPlayer::Inventory);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &ABasicPlayer::Interaction);
		EnhancedInputComponent->BindAction(MouseToggleAction, ETriggerEvent::Started, this, &ABasicPlayer::MouseToggle);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ABasicPlayer::Pause);
	}
	PlayerInputComponent->BindAction(TEXT("Action"), EInputEvent::IE_Pressed, this, &ABasicPlayer::Action);
}

void ABasicPlayer::Forward(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	if (Controller && (DirectionValue != FVector2D(0, 0))) {
		FVector DirectionForward = UKismetMathLibrary::GetForwardVector(FRotator(0.f, GetControlRotation().Yaw, 0.f));
		AddMovementInput(DirectionForward, DirectionValue.Y);
	}
}

void ABasicPlayer::Right(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	if (Controller && (DirectionValue != FVector2D(0, 0))) {
		FVector DirectionRight = UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, 0.f));
		AddMovementInput(DirectionRight, DirectionValue.X);
	}
}

void ABasicPlayer::Sight(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	if (Controller && (DirectionValue != FVector2D(0, 0))) {
		AddControllerYawInput(DirectionValue.X);
		AddControllerPitchInput(DirectionValue.Y);
	}
}

void ABasicPlayer::MouseToggle(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController->bShowMouseCursor == true) {
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else {
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}

void ABasicPlayer::Pause(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetPause(!bPauseWidget);
	PauseUIObject = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
	PauseUIObject->AddToViewport();
	bPauseWidget = true;
	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->SetShowMouseCursor(true);
}

void ABasicPlayer::Inventory(const FInputActionValue& Value)
{

}

void ABasicPlayer::Interaction(const FInputActionValue& Value)
{

}
