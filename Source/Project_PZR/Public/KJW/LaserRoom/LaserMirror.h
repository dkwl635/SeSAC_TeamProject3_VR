// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJW/KVRObjectInterface.h"
#include "LaserMirror.generated.h"

UCLASS()
class PROJECT_PZR_API ALaserMirror : public AActor , public IKVRObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserMirror();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//���� ������ �̿� �߻��ϱ�
	void NextLaserStart(const struct FHitResult& HitInfo, const FVector& InDir, const float& LaserLength, TArray<FVector>& Lines , bool& IsGoal ,bool& IsReal);

public:

	virtual bool  IsGrab();// { return !IsGrabbing; };

	//������ ������Ʈ ��� ����
	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//������ ������Ʈ ��� ����
	virtual void StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//��ư ����
	virtual void  OnButtonPressed(FHitResult& HitResult, EVRButton VRButton) override;
	//�潺ƽ �Է�
	virtual void OnThumbstickValue(class UMotionControllerComponent* MontionComp, bool IsRight, const FVector2D& Value) override;

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MirrorMeshComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* TempMirrorMeshComp;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* MirroBoxComp;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TempMirroBoxComp;

public:
	UPROPERTY(EditAnywhere, Category = "MirrorLaser")
	bool bDrawLaser = false;


private:
	UPROPERTY()
	TWeakObjectPtr<class AEndLaserPoint> EndLaserPoint;

	
	
public:
	//�ſ��� ������ ���� ũ�⿡�� 0.1 ������ ������ �ٿ����鼭 �վ����� ���ڲ�

	bool IsGrabbing = false;
	bool IsComplete = false;
	class UMotionControllerComponent* HandComp;
	FTimerHandle MoveToHandTimerHandle;
	FTimerHandle MoveToPlaceTimerHandle;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float MiniScale = 0.1;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	float OrginScale = 1.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float MoveToHandTime = 0.5f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	bool bEaseOutQuint = false;

	FVector OrginPos;
	FVector MovePos;
	float MoveToHandDeltatime = 0.02f;
	float MoveToHandTimer = 0.0f;


	void UpdateScale();
	void MoveToHand();
	void MoveToPlace();
	void DrawTempMirror();
	void TempMirrorRot(FRotator AddRot);
};
