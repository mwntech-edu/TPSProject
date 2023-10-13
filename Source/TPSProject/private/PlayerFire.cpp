// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFire.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

UPlayerFire::UPlayerFire() {
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(
		TEXT("SoundWave'/Game/SniperGun/Rifle.Rifle'"));

	if (tempSound.Succeeded()) {
		bulletSound = tempSound.Object;
	}
}
void UPlayerFire::BeginPlay() {
	_sniperUI = CreateWidget(GetWorld(), sniperUIFactory);
	_crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);
	_crosshairUI->AddToViewport();
	ChangeToSniperGun();
}
void UPlayerFire::SetupInputBinding(class UInputComponent* PlayerInputComponent) {
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPlayerFire::InputFire);
	PlayerInputComponent->BindAction(TEXT("GrenadeGun"), IE_Pressed, this, &UPlayerFire::ChangeToGrenadeGun);
	PlayerInputComponent->BindAction(TEXT("SniperGun"), IE_Pressed, this, &UPlayerFire::ChangeToSniperGun);
	PlayerInputComponent->BindAction(TEXT("Sniper"), IE_Pressed, this, &UPlayerFire::SniperAim);
	PlayerInputComponent->BindAction(TEXT("Sniper"), IE_Released, this, &UPlayerFire::SniperAim);
}

void UPlayerFire::InputFire() {
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

	auto controller = GetWorld()->GetFirstPlayerController();
	controller->PlayerCameraManager->StartCameraShake(cameraShake);

	auto anim = Cast<UPlayerAnim>(me->GetMesh()->GetAnimInstance());
	anim->PlayAttackAnim();

	if (bUsingGrenadeGun) {
		FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
	}
	else {
		FVector startPos = tpsCamComp->GetComponentLocation();
		FVector endPos = startPos + tpsCamComp->GetForwardVector() * 5000;
		FHitResult hitInfo;
		FCollisionQueryParams params;
		params.AddIgnoredActor(me);
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
		if (bHit) {
			/*FTransform bulletTrans;
			bulletTrans.SetLocation(hitInfo.ImpactPoint);*/
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, hitInfo.ImpactPoint);
			auto hitComp = hitInfo.GetComponent();
			if (hitComp && hitComp->IsSimulatingPhysics()) {
				FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 500000;
				hitComp->AddForce(force);
			}
			auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
			if (enemy) {
				auto enemyFSM = Cast<UEnemyFSM>(enemy);
				enemyFSM->OnDamageProcess();
			}
		}
	}
}
