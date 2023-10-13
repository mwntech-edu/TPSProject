// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()
public:
	void Turn(float value);
	void LookUp(float value);
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;
};
