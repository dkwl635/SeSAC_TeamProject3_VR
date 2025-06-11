// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LaserStageData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FLaserRoomActorData
{
    GENERATED_BODY()

public:
    // ������ ���� Ŭ���� 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ActorClass;

    // ���͵��� ������ ��ġ 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnLocation;

    // ���� ȸ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator SpawnRotation;

    // ������ ������ �� 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnScale = FVector::OneVector;
};

UCLASS(BlueprintType)
class PROJECT_PZR_API ULaserStageData : public UDataAsset
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserRoom")
	int32 Stage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserRoom")
    int32 NeedLaser = 1;

    //
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserRoom" 
    , Meta = (ToolTip = "0 : L , 1 : R , 2 : F , 3 : B"))
    int32 OpenDoorIndex = 0; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserRoom")
    TArray<FLaserRoomActorData> LaserRoomActorDatas;
		
};
