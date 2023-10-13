// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"

void UPlayerMove::Turn(float value) {
	me->AddControllerYawInput(value);
}
void UPlayerMove::LookUp(float value) {
	me->AddControllerPitchInput(value);
}
void UPlayerMove::SetupInputBinding(class UInputComponent* PlayerInputComponent) {
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &UPlayerMove::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &UPlayerMove::LookUp);
}
