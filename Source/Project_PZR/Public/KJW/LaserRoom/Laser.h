// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class PROJECT_PZR_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//�� ����Ʈ�� �׸��� �Լ�
	void SetBeamEnd(FVector StartPoint, FVector EndPoint);
	//����Ʈ ����� �Լ�
	void ResetBeam();

private:
	UPROPERTY(VisibleAnywhere, Category = "Laser")
	class USceneComponent* SceneComp;

	//������ ����Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Laser_Effects")
	class UNiagaraComponent* NiagaraComp;


};
