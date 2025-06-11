// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJW/KHelper.h"
#include "QPuzzleGameMode.generated.h"

/**
 * 
 */


DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateDelegate, EKGameState);

UCLASS()
class PROJECT_PZR_API AQPuzzleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	AQPuzzleGameMode();
protected:
	virtual void BeginPlay() override;

public:
	//���� ���� ����
	void ChangeLaserGameState(EKGameState NewLaserGameState);
	//���� �����ϱ�
	bool ChangeQPuzzle();
	//���伱��
	void SelectAnswer(int32 Index);
	//����Ȯ��
	void CheckAnswer();
	//�����ʱ�ȭ
	void ClearAnswer();
	//���� ����
	void FailAnser();
public:
	class UQPuzzleData* GetPuzzleData() { return CurQPuzzleData; }
	FText GetAnswerText() { return CurAnswer; }
	int32 GetPuzzleCount() { return PuzzleCount; }
	int32 GetGoalCount() { return GoalCount; }
private :
	void InitPuzzleDatas();

public:
	FUpdateDelegate UpdateStageDelegate;

	FUpdateDelegate UpdateAnswerDelegate;
private:
	EKGameState QPuzzleGameState = EKGameState::NONE;


	UPROPERTY(EditAnywhere, Category = "QPuzzleData", meta = (AllowPrivateAccess = true))
	TArray<class UQPuzzleData*> QPuzzleDatas;

	//�ߺ�������
	TArray<int32> QPuzzleIndex;
	class UQPuzzleData* CurQPuzzleData;

	UPROPERTY(VisibleAnywhere)
	int32 PuzzleCount = 0;

	UPROPERTY(EditAnywhere , Category = "QPuzzleData", meta = (AllowPrivateAccess = true))
	int32 GoalCount = 0;

	UPROPERTY(VisibleAnywhere)
	FText CurAnswer;

	FTimerHandle QPuzzleGameStateTimerHandle;

};
