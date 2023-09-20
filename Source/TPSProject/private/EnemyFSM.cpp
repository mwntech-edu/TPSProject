// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	default:
		break;
	}
}
void UEnemyFSM::IdleState() {
	// (Action) Play Idle Animation
	// (Event check)
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > idleDelayTime){
		// (State Transition) 
		mState = EEnemyState::Move;

		currentTime = 0;
	}
}
void UEnemyFSM::MoveState() {
	// (Action) 
	// (Event check)
	// (State Transition) mState = EEnemyState::
}
void UEnemyFSM::AttackState() {
	// (Action) 
	// (Event check)
	// (State Transition) mState = EEnemyState::
}
void UEnemyFSM::DamageState() {
	// (Action) 
	// (Event check)
	// (State Transition) mState = EEnemyState::
}
void UEnemyFSM::DieState() {
	// (Action) 
	// (Event check)
	// (State Transition) mState = EEnemyState::
}
