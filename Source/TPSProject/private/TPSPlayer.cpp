// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "PlayerMove.h"
#include "PlayerFire.h"
// Sets default values
ATPSPlayer::ATPSPlayer(){
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (TempMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, 0, -90));
	}
	// 3. Camera
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;

	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;
	// move
	bUseControllerRotationYaw = true;
	JumpMaxCount = 2;
	// gun
	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	gunMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT("SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	if (TempGunMesh.Succeeded()) {
		gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);
		gunMeshComp->SetRelativeLocation(FVector(-17, 10, -3));
		gunMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
	}
	// sniper gun
	sniperGunComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperMeshComp"));

	sniperGunComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempSniperMesh(TEXT("StaticMesh'/Game/SniperGun/sniper1.sniper1'"));
	if (TempSniperMesh.Succeeded()) {
		sniperGunComp->SetStaticMesh(TempSniperMesh.Object);
		sniperGunComp->SetRelativeLocation(FVector(-42, 7, 1));
		sniperGunComp->SetRelativeRotation(FRotator(0, 90, 0));
		sniperGunComp->SetRelativeScale3D(FVector(0.15f));
	}

	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT("PlayerMove"));
	//playerFire = CreateDefaultSubobject<UPlayerFire>(TEXT("PlayerFire"));
}// End of TPSPlayer()
// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	onInputBindingDelegate.Broadcast(PlayerInputComponent);

	//playerMove->SetupInputBinding(PlayerInputComponent);
	//playerFire->SetupInputBinding(PlayerInputComponent);
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay(){
	Super::BeginPlay();
	//GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Move();
}





