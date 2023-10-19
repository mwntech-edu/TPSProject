// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBaseComponent.h"
//#include "TPSProject.h"

void UPlayerBaseComponent::InitializeComponent() {
	Super::InitializeComponent();
	me = Cast<ATPSPlayer>(GetOwner());
	moveComp = me->GetCharacterMovement();
	me->onInputBindingDelegate.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);
}

// Called when the game starts
void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();
	//PRINT_LOG(TEXT("My Log : Component BeginPlay"));
}

// Called every frame
void UPlayerBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

