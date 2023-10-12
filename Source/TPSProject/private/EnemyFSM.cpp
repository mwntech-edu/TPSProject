// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Enemy.h"
#include "TPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include "TPSProject.h"
#include <Components/CapsuleComponent.h>
#include "EnemyAnim.h"

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
	// get player
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSPlayer::StaticClass());
	target = Cast<ATPSPlayer>(actor);
	// get self
	me = Cast<AEnemy>(GetOwner());
	anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());
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
		anim->animState = mState;
	}
}
void UEnemyFSM::MoveState() {
	// (Action) 
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());

	// (Event check)
	if (dir.Size() < attackRange) {
		// (State Transition) 
		mState = EEnemyState::Attack;
		anim->animState = mState;
		anim->bAttackPlay = true;
		currentTime = attackDelayTime;
	}
}
void UEnemyFSM::AttackState() {
	// (Action) 
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime) {
		PRINT_LOG(TEXT("Attack!!"));
		currentTime = 0;
		anim->bAttackPlay = true;
	}
	// (Event check)
	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange) {
		// (State Transition) 
		mState = EEnemyState::Move;
		anim->animState = mState;
	}
}
void UEnemyFSM::DamageState() {
	// (Action) 
	currentTime += GetWorld()->DeltaTimeSeconds;
	// (Event check)
	if (currentTime > damageDelayTime) {
		// (State Transition) 
		mState = EEnemyState::Idle;
		currentTime = 0;
		anim->animState = mState;
	}
}
void UEnemyFSM::DieState() {
	// (Action) 
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	me->SetActorLocation(P);
	if (P.Z < -200.f) {
		me->Destroy();
	}
	// (Event check)
	// (State Transition) mState = EEnemyState::
}
void UEnemyFSM::OnDamageProcess() {
	//me->Destroy();
	hp--;
	if (hp > 0) {
		mState = EEnemyState::Damage;

		currentTime = 0;
		int32 index = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"), index);
		anim->PlayDamageAnim(FName(*sectionName));
	}else {
		mState = EEnemyState::Die;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	anim->animState = mState;
}
