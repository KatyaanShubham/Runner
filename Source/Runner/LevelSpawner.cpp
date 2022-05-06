// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"

#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnLevel(true);
	SpawnLevel(false);
	SpawnLevel(false);
	SpawnLevel(false);
	
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSpawner::SpawnLevel(bool IsFirst)
{
	SpawnLocation = FVector(0.0f, 1410.0f, 0.0f);
	SpawnRotaion = FRotator(0, 90, 0);

	if (!IsFirst)
	{
		ABaseLevel* LastLevel = LevelList.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	RandomLevel = FMath::RandRange(1, 6);
	ABaseLevel* NewLevel = nullptr;

	if (RandomLevel == 1)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level1,
			SpawnLocation, SpawnRotaion, SpawnInfo);
	}

	else if (RandomLevel == 2)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level2, 
			SpawnLocation, SpawnRotaion, SpawnInfo);
	}

	else if (RandomLevel == 3)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level3,
			SpawnLocation, SpawnRotaion, SpawnInfo);
	}

	else if (RandomLevel == 4)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level4,
			SpawnLocation, SpawnRotaion, SpawnInfo);
	}

	else if (RandomLevel == 5)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level5,
			SpawnLocation, SpawnRotaion, SpawnInfo);
	}

	else if (RandomLevel == 6)
	{
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level6,
			SpawnLocation, SpawnRotaion, SpawnInfo);
	}

	if (NewLevel)
	{
		if (NewLevel->GetTrigger())
		{
			NewLevel->GetTrigger()->OnComponentBeginOverlap.
				AddDynamic(this, &ALevelSpawner::OnOverlapBegin);
		}
	}

	LevelList.Add(NewLevel);
	if (LevelList.Num() > 3)
	{
		LevelList.RemoveAt(0);
	}
	

}

void ALevelSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(false);
}

