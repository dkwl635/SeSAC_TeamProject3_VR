// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJW/KHelper.h"
#include "LaserRoomGameMode.generated.h"

/**
 * 
 */



DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateDelegate, EKGameState);

UCLASS()
class PROJECT_PZR_API ALaserRoomGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	ALaserRoomGameMode();
protected:
	virtual void BeginPlay() override;

public:
	//���� ���� ����
	void ChangeLaserGameState(EKGameState NewLaserGameState);

	//������ ���� ����
	void ResetStageActor();
	//���� ����
	void SpanwStage();

public:
	//������ Ǯ ����
	void SpawnLaser();
	//������ �ֱ�
 	class ALaser* GetLaser();
	//������ �����޴� 
	void ReturnLaser(class ALaser* Laser);

	int32 GetCurentStage() { return Stage; }
	void SetDisplayGmae(class  ALRStatgeDisplay* NewDisplay) { Display = NewDisplay; };
private:
	void SetDisplay();
public:
	void OpenDoor();

public:
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas")
	EKGameState LaserGameState = EKGameState::NONE;
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas")
	int32 NeedLaser = 1;
private:
	//�� ��� ��ü
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ALRoom> LaserRoomClass;
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas" , meta = (AllowPrivateAccess = true))
	TArray<class ULaserStageData*> StageDatas;
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas", meta = (AllowPrivateAccess = true))
	int32 CurStage = 0;
	

	UPROPERTY(EditAnywhere, Category = "LaserStageDatas", meta = (AllowPrivateAccess = true))
	int32 MaxStage = 1;
	FTimerHandle LaserGameStateTimerHandle;
public:
	FUpdateDelegate UpdateStageDelegate;
private:
	int32 Stage = 1;
	UPROPERTY()
	TArray<AActor*> SpawnedActors;

	//������ ������ ����Ʈ Ŭ����
	UPROPERTY(EditAnywhere, Category = "Laser_Effects" , meta = (AllowPrivateAccess = true))
	TSubclassOf<class ALaser> LaserClass;
	TQueue<class ALaser*> LaserPool;

private:
	class ALRStatgeDisplay* Display;
	
	TArray<class ALRoom*> RoomList;
	class ALRoom* PrevRoom;
;
	FVector RoomSpawnPos = FVector::ZeroVector;

private :
};
