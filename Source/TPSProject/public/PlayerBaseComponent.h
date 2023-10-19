// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerBaseComponent() {
		PrimaryComponentTick.bCanEverTick = false;
		bWantsInitializeComponent = true;
	}
	virtual void InitializeComponent() override;
	UPROPERTY()
		ATPSPlayer* me;
	UPROPERTY()
		UCharacterMovementComponent* moveComp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {};
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};
