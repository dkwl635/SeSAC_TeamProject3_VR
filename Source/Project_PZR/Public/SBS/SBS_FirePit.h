// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBS_FirePit.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_FirePit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBS_FirePit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* FireNiagara;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* ParticleSystem;
	
	int FireDamage = 10;
	void FireOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&
		SweepResult);

	void FireOverlapEnd(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
