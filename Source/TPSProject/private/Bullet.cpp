// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// collision
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComp->SetSphereRadius(13);
	RootComponent = collisionComp;
	// mesh
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp->SetupAttachment(collisionComp);
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bodyMeshComp->SetRelativeScale3D(FVector(0.25f));
	// projectile
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	movementComp->SetUpdatedComponent(collisionComp);
	movementComp->InitialSpeed = 5000;
	movementComp->MaxSpeed = 5000;
	movementComp->bShouldBounce = true;
	movementComp->Bounciness = 0.3f;
	//InitialLifeSpan = 2.0f;
}
void LambdaTestFunc() {
	//auto lambdaFunc = []()->void { UE_LOG(LogTemp, Warning, TEXT("Lambda test"))};
	int32 sum = 10;
	auto lambdaFunc = [&sum](int number)->void { 
		sum += number;
		//UE_LOG(LogTemp, Warning, TEXT("Lambda test"))
	};

	lambdaFunc(20);
	UE_LOG(LogTemp, Warning, TEXT("sum : %d"), sum);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	LambdaTestFunc();
	FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);
	GetWorld()->GetTimerManager().SetTimer(
		deathTimer, 
		FTimerDelegate::CreateLambda(
				[this]()->void 
				{ 
						Destroy(); 
				}
		), 
		2.0f, 
		false
	);
}
void ABullet::Die() {
	Destroy();
}
// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

