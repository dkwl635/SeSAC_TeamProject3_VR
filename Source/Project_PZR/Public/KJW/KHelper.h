// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EKGameState : uint8
{
	NONE UMETA(DisplayName = "None"),
	START UMETA(DisplayName = "Start"),
	INGAME UMETA(DisplayName = "InGame"),
	FAIL UMETA(DisplayName = "Fail"),
	CLEAR UMETA(DisplayName = "Clear"),
	FINISH UMETA(DisplayName = "Finish"),
};

 class PROJECT_PZR_API KHelper
{
public:
	static FVector GetReflectionVector(const FVector& IncidentVector, const FVector& SurfaceNormal)
	{
		//�⺻ ����
		//R == V - 2 * N * (V dot N)
		// 
		//V : �Ի� ���� => ���̵����� ���� ����
		//N : �浹 ǥ���� ��� ���� (���� ����)

		FVector V = IncidentVector; // �Ի� ����
		FVector N = SurfaceNormal;	// ��� ����

		//(V dot N)
		float DotProduct = FVector::DotProduct(V, N);  // 1. V�� N�� ���� ���
		//N * (V dot N)
		FVector ProjectionOntoNormal = DotProduct * N; // 2. ��� ���� ���� ã��
		// V - 2 * N * (V dot N)
		FVector ReflectionVector = V - 2 * ProjectionOntoNormal; // 3. �ݻ� ���� ���

		return ReflectionVector;
	}

	template <typename T>
	T Lerp(const T& A, const T& B, float Alpha)
	{
	
		//�⺻ Lerp ���� ]
		//Lerp = A + (B - A ) * Alpha

		//Easing �Լ��� �߰� �Ͽ� �پ��� Easing ȿ�� �߰�


	}
	

};


