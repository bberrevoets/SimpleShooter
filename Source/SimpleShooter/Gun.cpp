
#include "Gun.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return;
	}

	AController* OwnerController = OwnerPawn->GetController();

	if (OwnerController == nullptr)
	{
		return;
	}

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		End,
		ECC_GameTraceChannel1
	);

	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		
		if (AActor* HitActor = Hit.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
