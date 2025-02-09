// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 25;
	BaseLookRate = 45;
	BaseLookSideRange = 30;
	BaseLookUpRange = 30;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	Robot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Robot->SetupAttachment(RootComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Robot, FName("Head"));
	CameraBoom->TargetArmLength = 0; // The camera follows at this distance behind the character	

	Test = CreateDefaultSubobject<USceneComponent>(TEXT("Test"));
	Test->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(Test);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookAroundAtRate);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Controller != NULL && Value != 0)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::Turn(float Value)
{
	if (Controller != NULL && Value != 0)
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void APlayerCharacter::LookUpAtRate(float Value)
{
	float Pitch = FollowCamera->GetRelativeRotation().Pitch + (Value * BaseLookRate * GetWorld()->GetDeltaSeconds());
	FollowCamera->SetRelativeRotation(FRotator(FMath::Clamp(Pitch, -BaseLookUpRange, BaseLookUpRange), FollowCamera->GetRelativeRotation().Yaw, 0.0f));
}

void APlayerCharacter::LookAroundAtRate(float Value)
{
	float Yaw = FollowCamera->GetRelativeRotation().Yaw + (Value * BaseLookRate * GetWorld()->GetDeltaSeconds());
	FollowCamera->SetRelativeRotation(FRotator(FollowCamera->GetRelativeRotation().Pitch, FMath::Clamp(Yaw, -BaseLookSideRange, BaseLookSideRange), 0.0f));
}