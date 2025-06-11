// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/LaserRoom/StartLaserPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "KJW/LaserRoom/LaserMirror.h"

#include "KJW/LaserRoom/LaserRoomGameMode.h"
#include "KJW/LaserRoom/EndLaserPoint.h"
#include "KJW/LaserRoom/Laser.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"


// Sets default values
AStartLaserPoint::AStartLaserPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaserComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserComp"));
	SetRootComponent(LaserComp);

	LaserArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("LaserArrowComp"));
	LaserArrowComp->SetupAttachment(RootComponent);

	
	}

// Called when the game starts or when spawned
void AStartLaserPoint::BeginPlay()
{
	Super::BeginPlay();
	LRGM = Cast<ALaserRoomGameMode>(GetWorld()->GetAuthGameMode());
	ensure(LRGM);

	IsGoal = false;
}

void AStartLaserPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ReturnLaser();

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AStartLaserPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsStart) return;
	if (LaserDelayTimer < LaserDelay)
	{
		LaserDelayTimer += DeltaTime;
		return;
	}

	LaserDelayTimer = 0.0f;
	//StartLaser();
	//1. ������ ���
	StartSetLaser();
	//2. ���������� ������ ������ �׸���
	DrawLaser();
	
	//3. ���� �������� ���� �ߴ���
	CheckIsGoalLaser();

}



void AStartLaserPoint::StartSetLaser()
{
	//������ ����� �ʿ��� �ʱ�ȭ
	Lines.Empty();
	IsGoal = false;
	bool IsReal = true;
	//1.���� ��ġ ���� ����
	FVector StartPoint = LaserArrowComp->GetComponentLocation();
	FVector LaserDir = LaserArrowComp->GetForwardVector();
	FVector EndPoint = StartPoint + (LaserDir * LaserLength);
	
	Lines.Add(StartPoint);

	//2. ������ �浹 ã��
	FHitResult HitInfo;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartPoint, EndPoint, ECC_GameTraceChannel6
		, Params);
	
	ALaserMirror* Mirror = nullptr;
	//2 - 1�浹�� �ִٸ� -> �װ��� �ſ����� Ȯ�� �ϱ�
	if (bHit)
	{
		FVector Hitpoint = HitInfo.Location;
		EndPoint = Hitpoint;	
		Mirror = Cast<ALaserMirror>(HitInfo.GetActor());
	}
	Lines.Add(EndPoint);
	//2 - 2���� �ſ��̶�� ���� ������ ���
	if (Mirror)
	{
		//�ڿ��� ��� �������� üũ �ϱ�
		//�ſ� ������ ������ R Vector �̱� ������ ������ ����� ������ ���� ���͸� 
		//������ �м�
		//

		float dot = FVector::DotProduct(LaserDir, HitInfo.GetComponent()->GetRightVector());
		//UE_LOG(LogTemp, Warning, TEXT("%f"), dot);
		if (dot < 0)
		{
			Mirror->NextLaserStart(HitInfo, LaserDir, LaserLength, Lines, IsGoal, IsReal);
		}
	}

	if (!IsReal)
	{
		IsGoal = false;
	}


	if (bDrawLaser)
	{
		//Ȯ�ο� ����� ����
		DrawDebugLine(GetWorld(), LaserArrowComp->GetComponentLocation(), EndPoint, FColor::Red);
	}

}

void AStartLaserPoint::DrawLaser()
{
	if (Lines.Num() < 2) { return; }
	
	FVector StartPoint = Lines[0];
	FVector EndPoint = Lines[1];
	int32 NeedLaser = Lines.Num();

	GetLaser(NeedLaser);

	for (int i = 1; i < NeedLaser; ++i)
	{
		EndPoint = Lines[i];
		ALaser* DrawLaser = Lasers[i];
		DrawLaser->SetBeamEnd(StartPoint , EndPoint);
		StartPoint = EndPoint;
	}

}

void AStartLaserPoint::GetLaser(int32 Count)
{
	if (Lasers.Num() == Count) { return;}

	if (!Lasers.IsEmpty()) { ReturnLaser(); }

	for (int32 i = 0; i < Count; ++i)
	{
		Lasers.Add(LRGM->GetLaser());
	}
}

void AStartLaserPoint::ReturnLaser()
{
	for (int32 i = 0; i < Lasers.Num(); ++i)
	{
		LRGM->ReturnLaser(Lasers[i]);
	}
	
	Lasers.Empty();
}

void AStartLaserPoint::CheckIsGoalLaser()
{
	if (!CurentEndLaserPoint)
	{
		CurentEndLaserPoint =
			Cast<AEndLaserPoint>( UGameplayStatics::GetActorOfClass(GetWorld() , AEndLaserPoint::StaticClass()));
	}

	if (!CurentEndLaserPoint) { return; }


	if (IsGoal)
	{
		CurentEndLaserPoint->AddMirrorPoint(this);
	}
	else
	{
		CurentEndLaserPoint->RemoveMirrorPoint(this);
	}
}

