// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	if (Value > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Forward"));
	}
	else if (Value < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Backwards"));
	}
}

void APlayerCharacter::Turn(float Value)
{
	if (Value > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnRight"));
	}
	else if (Value < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnLeft"));
	}
}

void APlayerCharacter::LookUpAtRate(float Value)
{
	if (Value > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LookUp"));
	}
	else if (Value < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LookDown"));
	}
}

void APlayerCharacter::LookAroundAtRate(float Value)
{
	if (Value > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LookRight"));
	}
	else if (Value < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LookLeft"));
	}
}