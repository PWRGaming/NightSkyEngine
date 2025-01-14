// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleActor.h"
#include "Battle/Actors/BattleActor.h"
#include "FighterGameState.h"
#include "NiagaraComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattleActor::ABattleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;
}

// Called when the game starts or when spawned
void ABattleActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABattleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (LinkedParticle != nullptr)
	{
		FVector Location = FVector(0, Parent.Get()->GetInternalValue(InternalValue::VAL_PosX) / COORD_SCALE, Parent.Get()->GetInternalValue(InternalValue::VAL_PosY) / COORD_SCALE);
		LinkedParticle->SetWorldLocation(Location);
	}
	if (Parent.IsValid())
	{
		if (Parent.Get()->IsActive)
		{
			if (!Parent.Get()->FacingRight)
			{
				SetActorScale3D(FVector(1, -1, 1));
			}
			else
			{
				SetActorScale3D(FVector(1, 1, 1));
			}
			SetActorLocation(FVector(0, float(Parent.Get()->GetInternalValue(VAL_PosX)) / COORD_SCALE, float(Parent.Get()->GetInternalValue(VAL_PosY)) / COORD_SCALE)); //set visual location and scale in unreal
			if (LinkedParticle != nullptr)
			{
				LinkedParticle->SetWorldLocation(GetActorLocation());
				LinkedParticle->SetVisibility(true);
			}
		}
	}
}

BattleActor* ABattleActor::GetParent()
{
	return Parent.Get();
}

void ABattleActor::SetParent(BattleActor* InActor)
{
	Parent = TSharedPtr<BattleActor>(InActor);
}

void ABattleActor::Update()
{
	Parent.Get()->StateVal1 = StateVal1;
	Parent.Get()->StateVal2 = StateVal2;
	Parent.Get()->StateVal3 = StateVal3;
	Parent.Get()->StateVal4 = StateVal4;
	Parent.Get()->StateVal5 = StateVal5;
	Parent.Get()->StateVal6 = StateVal6;
	Parent.Get()->StateVal7 = StateVal7;
	Parent.Get()->StateVal8 = StateVal8;
	Parent.Get()->AnimTime = AnimTime;
	Parent.Get()->DefaultCommonAction = DefaultCommonAction;
}

void ABattleActor::OnLoadGameState()
{
	StateVal1 = Parent.Get()->StateVal1;
	StateVal1 = Parent.Get()->StateVal2;
	StateVal1 = Parent.Get()->StateVal3;
    StateVal4 = Parent.Get()->StateVal4;
    StateVal5 = Parent.Get()->StateVal5;
	StateVal6 = Parent.Get()->StateVal6;
    StateVal7 = Parent.Get()->StateVal7;
    StateVal8 = Parent.Get()->StateVal8;
    AnimTime = Parent.Get()->AnimTime;
    DefaultCommonAction = Parent.Get()->DefaultCommonAction;
}

void ABattleActor::SetPosX(int InPosX)
{
	Parent.Get()->SetPosX(InPosX);
}

void ABattleActor::SetPosY(int InPosY)
{
	Parent.Get()->SetPosY(InPosY);
}

void ABattleActor::AddPosX(int InPosX)
{
	Parent.Get()->AddPosX(InPosX);
}

void ABattleActor::AddPosXRaw(int InPosX)
{
	Parent.Get()->AddPosXRaw(InPosX);
}

void ABattleActor::AddPosY(int InPosY)
{
	Parent.Get()->AddPosY(InPosY);
}

void ABattleActor::SetSpeedX(int InSpeedX)
{
	Parent.Get()->SetSpeedX(InSpeedX);
}

void ABattleActor::SetSpeedY(int InSpeedY)
{
	Parent.Get()->SetSpeedY(InSpeedY);
}

void ABattleActor::SetGravity(int InGravity)
{
	Parent.Get()->SetGravity(InGravity);
}

void ABattleActor::HaltMomentum()
{
	Parent.Get()->HaltMomentum();
}

void ABattleActor::SetPushWidthExpand(int Expand)
{
	Parent.Get()->SetPushWidthExpand(Expand);
}

int ABattleActor::GetInternalValue(EInternalValue InInternalValue, EObjType InObjType)
{
	return Parent.Get()->GetInternalValue((InternalValue)InInternalValue, (ObjType)InObjType);
}

bool ABattleActor::IsOnFrame(int Frame)
{
	if (Frame == AnimTime)
	{
		return true;
	}
	return false;
}

bool ABattleActor::IsStopped()
{
	return Parent.Get()->IsStopped();
}

void ABattleActor::SetCelName(FString InCelName)
{
	CelName = InCelName;
	Parent.Get()->SetCelName(TCHAR_TO_ANSI(*InCelName));
}

void ABattleActor::SetHitEffectName(FString InHitEffectName)
{
	Parent.Get()->SetHitEffectName(TCHAR_TO_ANSI(*InHitEffectName));
}

void ABattleActor::AddSpeedX(int InSpeedX)
{
	Parent.Get()->AddSpeedX(InSpeedX);
}

void ABattleActor::AddSpeedY(int InSpeedY)
{
	Parent.Get()->AddSpeedY(InSpeedY);
}

void ABattleActor::SetSpeedXPercent(int32 Percent)
{
	Parent.Get()->SetSpeedXPercent(Percent);
}

void ABattleActor::SetSpeedXPercentPerFrame(int32 Percent)
{
	Parent.Get()->SetSpeedXPercentPerFrame(Percent);
}

void ABattleActor::SetInertia(int InInertia)
{
	Parent.Get()->SetInertia(InInertia);
}

void ABattleActor::ClearInertia()
{
	Parent.Get()->ClearInertia();
}

void ABattleActor::EnableInertia()
{
	Parent.Get()->EnableInertia();
}

void ABattleActor::DisableInertia()
{
	Parent.Get()->DisableInertia();
}

void ABattleActor::SetFacing(bool NewFacingRight)
{
	Parent.Get()->SetFacing(NewFacingRight);
}

void ABattleActor::FlipCharacter()
{
	Parent.Get()->FlipCharacter();
}

void ABattleActor::EnableFlip(bool Enabled)
{
	Parent.Get()->EnableFlip(Enabled);
}

void ABattleActor::GetBoxes()
{
	CollisionBoxes.Empty();
	if (Player->CollisionData != nullptr)
	{
		for (int i = 0; i < Player->CollisionData->CollisionFrames.Num(); i++)
		{
			if (Player->CollisionData->CollisionFrames[i].Name == Parent.Get()->CelNameInternal.GetString())
			{
				for (int j = 0; j < CollisionArraySize; j++)
				{
					if (j < Player->CollisionData->CollisionFrames[i].CollisionBoxes.Num())
					{
						CollisionBox CollisionBoxInternal;
						CollisionBoxInternal.Type = (BoxType)Player->CollisionData->CollisionFrames[i].CollisionBoxes[j]->Type.GetValue();
						CollisionBoxInternal.PosX = Player->CollisionData->CollisionFrames[i].CollisionBoxes[j]->PosX;
						CollisionBoxInternal.PosY = Player->CollisionData->CollisionFrames[i].CollisionBoxes[j]->PosY;
						CollisionBoxInternal.SizeX = Player->CollisionData->CollisionFrames[i].CollisionBoxes[j]->SizeX;
						CollisionBoxInternal.SizeY = Player->CollisionData->CollisionFrames[i].CollisionBoxes[j]->SizeY;
						CollisionBoxes.Add(CollisionBoxInternal);
						Parent.Get()->CollisionBoxes[j] = CollisionBoxInternal;
					}
					else
					{
						Parent.Get()->CollisionBoxes[j].Type = Hurtbox;
						Parent.Get()->CollisionBoxes[j].PosX = -10000000;
						Parent.Get()->CollisionBoxes[j].PosY = -10000000;
						Parent.Get()->CollisionBoxes[j].SizeX = 0;
						Parent.Get()->CollisionBoxes[j].SizeY = 0;
					}
				}
				return;
			}
		}
		for (int j = 0; j < CollisionArraySize; j++)
		{
			Parent.Get()->CollisionBoxes[j].Type = Hurtbox;
			Parent.Get()->CollisionBoxes[j].PosX = -10000000;
			Parent.Get()->CollisionBoxes[j].PosY = -10000000;
			Parent.Get()->CollisionBoxes[j].SizeX = 0;
			Parent.Get()->CollisionBoxes[j].SizeY = 0;
		}
	}
}

//for collision viewer

template<typename T>
constexpr auto min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
constexpr auto max(T a, T b)
{
	return a > b ? a : b;
}
static void clip_line_y(
	const FVector2D &line_a, const FVector2D &line_b,
	float min_x, float max_x,
	float *min_y, float *max_y)
{
	const auto delta = line_b - line_a;

	if (abs(delta.X) > FLT_EPSILON) {
		const auto slope = delta.Y / delta.X;
		const auto intercept = line_a.Y - slope * line_a.X;
		*min_y = slope * min_x + intercept;
		*max_y = slope * max_x + intercept;
	} else {
		*min_y = line_a.Y;
		*max_y = line_b.Y;
	}

	if (*min_y > *max_y)
		std::swap(*min_y, *max_y);
}

bool line_box_intersection(
	const FVector2D &box_min, const FVector2D &box_max,
	const FVector2D &line_a, const FVector2D &line_b,
	float *entry_fraction, float *exit_fraction)
{
	// No intersection if line runs along the edge of the box
	if (line_a.X == line_b.X && (line_a.X == box_min.X || line_a.X == box_max.X))
		return false;

	if (line_a.Y == line_b.Y && (line_a.Y == box_min.Y || line_a.Y == box_max.Y))
		return false;

	// Clip X values to segment within box_min.X and box_max.X
	const auto min_x = max(min(line_a.X, line_b.X), box_min.X);
	const auto max_x = min(max(line_a.X, line_b.X), box_max.X);

	// Check if the line is in the bounds of the box on the X axis
	if (min_x > max_x)
		return false;

	// Clip Y values to segment within min_x and max_x
	float min_y, max_y;
	clip_line_y(line_a, line_b, min_x, max_x, &min_y, &max_y);

	// Clip Y values to segment within box_min.Y and box_max.Y
	min_y = max(min_y, (float)box_min.Y);
	max_y = min(max_y, (float)box_max.Y);

	// Check if the clipped line is in the bounds of the box on the Y axis
	if (min_y > max_y)
		return false;

	const FVector2D entry(
		line_a.X < line_b.X ? min_x : max_x,
		line_a.Y < line_b.Y ? min_y : max_y);

	const FVector2D exit(
		line_a.X > line_b.X ? min_x : max_x,
		line_a.Y > line_b.Y ? min_y : max_y);

	const auto length = (line_b - line_a).Size();
	*entry_fraction = (entry - line_a).Size() / length;
	*exit_fraction = (exit - line_a).Size() / length;

	return true;
}

void ABattleActor::CollisionView()
{
	TArray<TArray<FVector2D>> Corners;
	TArray<TArray<TArray<FVector2D>>> Lines;
	int PosX = Parent.Get()->GetInternalValue(InternalValue::VAL_PosX);
	int PosY = Parent.Get()->GetInternalValue(InternalValue::VAL_PosY);
	if (CollisionBoxes.Num() != 0)
	{
		for (int i = 0; i < CollisionBoxes.Num(); i++)
		{
			TArray<FVector2D> CurrentCorners;
			if (Parent.Get()->FacingRight)
			{
				CurrentCorners.Add(FVector2D(float(CollisionBoxes[i].PosX + PosX) / COORD_SCALE - float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE -  float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
				CurrentCorners.Add(FVector2D(float(CollisionBoxes[i].PosX + PosX) / COORD_SCALE + float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE -  float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
				CurrentCorners.Add(FVector2D(float(CollisionBoxes[i].PosX + PosX) / COORD_SCALE + float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE + float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
				CurrentCorners.Add(FVector2D(float(CollisionBoxes[i].PosX + PosX) / COORD_SCALE - float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE + float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
			}
			else
			{
				CurrentCorners.Add(FVector2D(float(-CollisionBoxes[i].PosX + PosX) / COORD_SCALE - float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE -  float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
				CurrentCorners.Add(FVector2D(float(-CollisionBoxes[i].PosX + PosX) / COORD_SCALE + float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE -  float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
				CurrentCorners.Add(FVector2D(float(-CollisionBoxes[i].PosX + PosX) / COORD_SCALE + float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE + float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
				CurrentCorners.Add(FVector2D(float(-CollisionBoxes[i].PosX + PosX) / COORD_SCALE - float(CollisionBoxes[i].SizeX) / COORD_SCALE / 2,
					float(CollisionBoxes[i].PosY + PosY) / COORD_SCALE + float(CollisionBoxes[i].SizeY) / COORD_SCALE / 2));
			}
			Corners.Add(CurrentCorners);
			TArray<TArray<FVector2D>> CurrentLines;
			for (int j = 0; j < 4; j++)
			{
				CurrentLines.Add(TArray { CurrentCorners[j] , CurrentCorners[(j + 1) % 4] } );
			}
			Lines.Add(CurrentLines);
		}
		for (int i = 0; i < CollisionBoxes.Num(); i++)
		{
			FLinearColor color;
			if (CollisionBoxes[i].Type == BoxType::Hitbox)
				color = FLinearColor(1.f, 0.f, 0.f, .25f);
			else if (Parent.Get()->IsAttacking)
				color = FLinearColor(0.f, 1.f, 1.f, .25f);
			else
				color = FLinearColor(0.f, 1.f, 0.f, .25f);

			for (const auto LineSet : Lines[i])
			{
				auto start = LineSet[0];
				auto end = LineSet[1];
				DrawDebugLine(GetWorld(), FVector(0, start.X, start.Y), FVector(0, end.X, end.Y), color.ToFColor(false), false, 1 / 60, 255, 2.f);
			}
		}
	}
	TArray<FVector2D> CurrentCorners;
	CurrentCorners.Add(FVector2D(Parent.Get()->L / COORD_SCALE, Parent.Get()->B / COORD_SCALE));
	CurrentCorners.Add(FVector2D(Parent.Get()->R / COORD_SCALE, Parent.Get()->B / COORD_SCALE));
	CurrentCorners.Add(FVector2D(Parent.Get()->R / COORD_SCALE, Parent.Get()->T / COORD_SCALE));
	CurrentCorners.Add(FVector2D(Parent.Get()->L / COORD_SCALE, Parent.Get()->T / COORD_SCALE));
	TArray<TArray<FVector2D>> CurrentLines;
	for (int j = 0; j < 4; j++)
	{
		CurrentLines.Add(TArray { CurrentCorners[j] , CurrentCorners[(j + 1) % 4] } );
	}
	FLinearColor color = FLinearColor(1.f, 1.f, 0.f, .2f);

	for (const auto LineSet : CurrentLines)
	{
		auto start = LineSet[0];
		auto end = LineSet[1];
		DrawDebugLine(GetWorld(), FVector(0, start.X, start.Y), FVector(0, end.X, end.Y), color.ToFColor(false), false,1 / 60, 255, 2.f);
	}
}

//collision viewer end

void ABattleActor::EnableHit(bool Enabled)
{
	Parent.Get()->EnableHit(Enabled);
}

void ABattleActor::SetAttacking(bool Attacking)
{
	Parent.Get()->SetAttacking(Attacking);
}

void ABattleActor::SetHeadAttribute(bool HeadAttribute)
{
	Parent.Get()->SetHeadAttribute(HeadAttribute);
}

void ABattleActor::SetHitEffect(FHitEffect InHitEffect)
{
	HitEffect InternalHitEFfect;
	InternalHitEFfect.AttackLevel = InHitEffect.AttackLevel;
	InternalHitEFfect.BlockType = (BlockType)InHitEffect.BlockType.GetValue();
	InternalHitEFfect.Hitstun = InHitEffect.Hitstun;
	InternalHitEFfect.Blockstun = InHitEffect.Blockstun;
	InternalHitEFfect.Untech = InHitEffect.Untech;
	InternalHitEFfect.Hitstop = InHitEffect.Hitstop;
	InternalHitEFfect.HitDamage = InHitEffect.HitDamage;
	InternalHitEFfect.MinimumDamagePercent = InHitEffect.MinimumDamagePercent;
	InternalHitEFfect.ChipDamagePercent = InHitEffect.ChipDamagePercent;
	InternalHitEFfect.InitialProration = InHitEffect.InitialProration;
	InternalHitEFfect.ForcedProration = InHitEffect.ForcedProration;
	InternalHitEFfect.HitPushbackX = InHitEffect.HitPushbackX;
	InternalHitEFfect.AirHitPushbackX = InHitEffect.AirHitPushbackX;
	InternalHitEFfect.AirHitPushbackY = InHitEffect.AirHitPushbackY;
	InternalHitEFfect.HitGravity = InHitEffect.HitGravity;
	InternalHitEFfect.HitAngle = InHitEffect.HitAngle;
	InternalHitEFfect.GroundHitAction = (HitAction)InHitEffect.GroundHitAction.GetValue();
	InternalHitEFfect.AirHitAction = (HitAction)InHitEffect.AirHitAction.GetValue();
	InternalHitEFfect.KnockdownTime = InHitEffect.KnockdownTime;

	GroundBounceEffect InternalGroundBounceEffect;
	InternalGroundBounceEffect.GroundBounceCount = InHitEffect.GroundBounceEffect.GroundBounceCount;
	InternalGroundBounceEffect.GroundBounceUntech = InHitEffect.GroundBounceEffect.GroundBounceUntech;
	InternalGroundBounceEffect.GroundBounceXSpeed = InHitEffect.GroundBounceEffect.GroundBounceXSpeed;
	InternalGroundBounceEffect.GroundBounceYSpeed = InHitEffect.GroundBounceEffect.GroundBounceYSpeed;
	InternalGroundBounceEffect.GroundBounceGravity = InHitEffect.GroundBounceEffect.GroundBounceGravity;
	InternalHitEFfect.GroundBounceEffect = InternalGroundBounceEffect;

	WallBounceEffect InternalWallBounceEffect;
	InternalWallBounceEffect.WallBounceCount = InHitEffect.WallBounceEffect.WallBounceCount;
	InternalWallBounceEffect.WallBounceUntech = InHitEffect.WallBounceEffect.WallBounceUntech;
	InternalWallBounceEffect.WallBounceXSpeed = InHitEffect.WallBounceEffect.WallBounceXSpeed;
	InternalWallBounceEffect.WallBounceYSpeed = InHitEffect.WallBounceEffect.WallBounceYSpeed;
	InternalWallBounceEffect.WallBounceGravity = InHitEffect.WallBounceEffect.WallBounceGravity;
	InternalWallBounceEffect.WallBounceInCornerOnly = InHitEffect.WallBounceEffect.WallBounceInCornerOnly;
	InternalHitEFfect.WallBounceEffect = InternalWallBounceEffect;

	InternalHitEFfect.SFXType = (HitSFXType)InHitEffect.SFXType;
	InternalHitEFfect.VFXType = (HitVFXType)InHitEffect.VFXType;
	InternalHitEFfect.DeathCamOverride = InHitEffect.DeathCamOverride;

	Parent.Get()->SetHitEffect(InternalHitEFfect);
}

void ABattleActor::SetCounterHitEffect(FHitEffect InHitEffect)
{

	HitEffect InternalHitEFfect;
	InternalHitEFfect.AttackLevel = InHitEffect.AttackLevel;
	InternalHitEFfect.BlockType = (BlockType)InHitEffect.BlockType.GetValue();
	InternalHitEFfect.Hitstun = InHitEffect.Hitstun;
	InternalHitEFfect.Blockstun = InHitEffect.Blockstun;
	InternalHitEFfect.Untech = InHitEffect.Untech;
	InternalHitEFfect.Hitstop = InHitEffect.Hitstop;
	InternalHitEFfect.HitDamage = InHitEffect.HitDamage;
	InternalHitEFfect.MinimumDamagePercent = InHitEffect.MinimumDamagePercent;
	InternalHitEFfect.ChipDamagePercent = InHitEffect.ChipDamagePercent;
	InternalHitEFfect.InitialProration = InHitEffect.InitialProration;
	InternalHitEFfect.ForcedProration = InHitEffect.ForcedProration;
	InternalHitEFfect.HitPushbackX = InHitEffect.HitPushbackX;
	InternalHitEFfect.AirHitPushbackX = InHitEffect.AirHitPushbackX;
	InternalHitEFfect.AirHitPushbackY = InHitEffect.AirHitPushbackY;
	InternalHitEFfect.HitGravity = InHitEffect.HitGravity;
	InternalHitEFfect.HitAngle = InHitEffect.HitAngle;
	InternalHitEFfect.GroundHitAction = (HitAction)InHitEffect.GroundHitAction.GetValue();
	InternalHitEFfect.AirHitAction = (HitAction)InHitEffect.AirHitAction.GetValue();
	InternalHitEFfect.KnockdownTime = InHitEffect.KnockdownTime;

	GroundBounceEffect InternalGroundBounceEffect;
	InternalGroundBounceEffect.GroundBounceCount = InHitEffect.GroundBounceEffect.GroundBounceCount;
	InternalGroundBounceEffect.GroundBounceUntech = InHitEffect.GroundBounceEffect.GroundBounceUntech;
	InternalGroundBounceEffect.GroundBounceXSpeed = InHitEffect.GroundBounceEffect.GroundBounceXSpeed;
	InternalGroundBounceEffect.GroundBounceYSpeed = InHitEffect.GroundBounceEffect.GroundBounceYSpeed;
	InternalGroundBounceEffect.GroundBounceGravity = InHitEffect.GroundBounceEffect.GroundBounceGravity;
	InternalHitEFfect.GroundBounceEffect = InternalGroundBounceEffect;

	WallBounceEffect InternalWallBounceEffect;
	InternalWallBounceEffect.WallBounceCount = InHitEffect.WallBounceEffect.WallBounceCount;
	InternalWallBounceEffect.WallBounceUntech = InHitEffect.WallBounceEffect.WallBounceUntech;
	InternalWallBounceEffect.WallBounceXSpeed = InHitEffect.WallBounceEffect.WallBounceXSpeed;
	InternalWallBounceEffect.WallBounceYSpeed = InHitEffect.WallBounceEffect.WallBounceYSpeed;
	InternalWallBounceEffect.WallBounceGravity = InHitEffect.WallBounceEffect.WallBounceGravity;
	InternalWallBounceEffect.WallBounceInCornerOnly = InHitEffect.WallBounceEffect.WallBounceInCornerOnly;
	InternalHitEFfect.WallBounceEffect = InternalWallBounceEffect;

	InternalHitEFfect.SFXType = (HitSFXType)InHitEffect.SFXType;
	InternalHitEFfect.VFXType = (HitVFXType)InHitEffect.VFXType;
	InternalHitEFfect.DeathCamOverride = InHitEffect.DeathCamOverride;

	Parent.Get()->SetCounterHitEffect(InternalHitEFfect);}

void ABattleActor::CreateCommonParticle(FString Name, EPosType PosType, FVector Offset, FRotator Rotation)
{
	if (Player->CommonParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->CommonParticleData->ParticleDatas)
		{
			if (ParticleStruct.Name == Name)
			{
				FVector FinalLocation;
				if (!Parent.Get()->FacingRight)
					Offset = FVector(Offset.X, -Offset.Y, Offset.Z);
				switch (PosType)
				{
				case EPosType::POS_Player:
					FinalLocation = Offset + GetActorLocation();
					break;
				case EPosType::POS_Enemy:
					FinalLocation = Offset + Player->Enemy->GetActorLocation();
					break;
				case EPosType::POS_Hit:
					FinalLocation = Offset + FVector(0, Parent.Get()->HitPosX / COORD_SCALE, Parent.Get()->HitPosY / COORD_SCALE);
					break;
				default:
					FinalLocation = Offset + GetActorLocation();
					break;
				}
				GameState->ParticleManager->NiagaraComponents.Add(UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ParticleStruct.ParticleSystem, FinalLocation, Rotation, GetActorScale()));
				GameState->ParticleManager->NiagaraComponents.Last()->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
				GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableBool("NeedsRollback", true);
				GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableFloat("SpriteRotate", Rotation.Pitch);
				if (!Parent.Get()->FacingRight)
				{
					GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableVec2("UVScale", FVector2D(-1, 1));
					GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableVec2("PivotOffset", FVector2D(0, 0.5));
					GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableFloat("SpriteRotate", -Rotation.Pitch);
				}
				break;
			}
		}
	}
}

void ABattleActor::CreateCharaParticle(FString Name, EPosType PosType, FVector Offset, FRotator Rotation)
{
	if (Player->ParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->ParticleData->ParticleDatas)
		{
			if (ParticleStruct.Name == Name)
			{
				FVector FinalLocation;
				if (!Parent.Get()->FacingRight)
					Offset = FVector(Offset.X, -Offset.Y, Offset.Z);
				switch (PosType)
				{
				case EPosType::POS_Player:
					FinalLocation = Offset + GetActorLocation();
					break;
				case EPosType::POS_Enemy:
					FinalLocation = Offset + Player->Enemy->GetActorLocation();
					break;
				case EPosType::POS_Hit:
					FinalLocation = Offset + FVector(0, Parent.Get()->HitPosX / COORD_SCALE, Parent.Get()->HitPosY / COORD_SCALE);
					break;
				default:
					FinalLocation = Offset + GetActorLocation();
					break;
				}
				GameState->ParticleManager->NiagaraComponents.Add(UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ParticleStruct.ParticleSystem, FinalLocation, Rotation, GetActorScale()));
				GameState->ParticleManager->NiagaraComponents.Last()->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
				GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableBool("NeedsRollback", true);
				GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableFloat("SpriteRotate", Rotation.Pitch);
				if (!Parent.Get()->FacingRight)
				{
					GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableVec2("UVScale", FVector2D(-1, 1));
					GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableVec2("PivotOffset", FVector2D(0, 1));
					GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableFloat("SpriteRotate", -Rotation.Pitch);
				}
				break;
			}
		}
	}
}

void ABattleActor::LinkCharaParticle(FString Name)
{
	if (Player->ParticleData != nullptr)
	{
		for (FParticleStruct ParticleStruct : Player->ParticleData->ParticleDatas)
		{
			if (ParticleStruct.Name == Name)
			{
				FVector Scale;
				if (!Parent.Get()->FacingRight)
				{
					Scale = FVector(1, -1, 1);
				}
				else
				{
					Scale = FVector(1, 1, 1);
				}
				GameState->ParticleManager->NiagaraComponents.Add(UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ParticleStruct.ParticleSystem, GetActorLocation(), FRotator::ZeroRotator, Scale));
				GameState->ParticleManager->NiagaraComponents.Last()->SetAgeUpdateMode(ENiagaraAgeUpdateMode::DesiredAge);
				GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableBool("NeedsRollback", true);
				LinkedParticle = GameState->ParticleManager->NiagaraComponents.Last();
				if (!Parent.Get()->FacingRight)
					GameState->ParticleManager->NiagaraComponents.Last()->SetNiagaraVariableVec2("UVScale", FVector2D(-1, 1));
				break;
			}
		}
	}
}

void ABattleActor::PlayCommonSound(FString Name)
{
	if (Player->CommonSoundData != nullptr)
	{
		for (FSoundDataStruct SoundStruct : Player->CommonSoundData->SoundDatas)
		{
			if (SoundStruct.Name == Name)
			{
				GameState->PlayCommonAudio(SoundStruct.SoundWave, SoundStruct.MaxDuration);
				break;
			}
		}
	}
}

void ABattleActor::PlayCharaSound(FString Name)
{
	if (Player->SoundData != nullptr)
	{
		for (FSoundDataStruct SoundStruct : Player->SoundData->SoundDatas)
		{
			if (SoundStruct.Name == Name)
			{
				GameState->PlayCharaAudio(SoundStruct.SoundWave, SoundStruct.MaxDuration);
				break;
			}
		}
	}
}

void ABattleActor::AttachToSocketOfObject(FString InSocketName, FVector Offset, EObjType ObjType)
{
	SocketName = InSocketName;
	SocketObj = ObjType;
	SocketOffset = Offset;
}

void ABattleActor::DetachFromSocket()
{
	SocketName = "";
	SocketObj = EObjType::OBJ_Self;
}

void ABattleActor::PauseRoundTimer(bool Pause)
{
	Parent.Get()->PauseRoundTimer(Pause);
}

void ABattleActor::SetObjectID(int InObjectID)
{
	Parent.Get()->SetObjectID(InObjectID);
}

void ABattleActor::DeactivateIfBeyondBounds()
{
	Parent.Get()->DeactivateIfBeyondBounds();
}

void ABattleActor::DeactivateObject()
{
	Parent.Get()->DeactivateObject();
	if (LinkedParticle != nullptr)
	{
		LinkedParticle->SetVisibility(false);
	}
}

ABattleActor* ABattleActor::GetBattleActor(EObjType Type)
{
	//TODO: fix once player character and game state are set up
	/*
	switch (Type)
	{
	case OBJ_Self:
		return this;
	case OBJ_Enemy:
		return Player->Enemy;
	case OBJ_Parent:
		return Player;
	case OBJ_Child0:
		if (IsPlayer && Player->StoredBattleActors[0])
			if (Player->StoredBattleActors[0]->IsActive)
				return Player->StoredBattleActors[0];
		return nullptr;
	case OBJ_Child1:
		if (IsPlayer && Player->StoredBattleActors[1])
			if (Player->StoredBattleActors[1]->IsActive)
				return Player->StoredBattleActors[1];
		return nullptr;
	case OBJ_Child2:
		if (IsPlayer && Player->StoredBattleActors[2])
			if (Player->StoredBattleActors[2]->IsActive)
				return Player->StoredBattleActors[2];
		return nullptr;
	case OBJ_Child3:
		if (IsPlayer && Player->StoredBattleActors[3])
			if (Player->StoredBattleActors[3]->IsActive)
				return Player->StoredBattleActors[3];
		return nullptr;
	case OBJ_Child4:
		if (IsPlayer && Player->StoredBattleActors[4])
			if (Player->StoredBattleActors[4]->IsActive)
				return Player->StoredBattleActors[4];
		return nullptr;
	case OBJ_Child5:
		if (IsPlayer && Player->StoredBattleActors[5])
			if (Player->StoredBattleActors[5]->IsActive)
				return Player->StoredBattleActors[5];
		return nullptr;
	case OBJ_Child6:
		if (IsPlayer && Player->StoredBattleActors[6])
			if (Player->StoredBattleActors[6]->IsActive)
				return Player->StoredBattleActors[6];
		return nullptr;
	case OBJ_Child7:
		if (IsPlayer && Player->StoredBattleActors[7])
			if (Player->StoredBattleActors[7]->IsActive)
				return Player->StoredBattleActors[7];
		return nullptr;
	case OBJ_Child8:
		if (IsPlayer && Player->StoredBattleActors[8])
			if (Player->StoredBattleActors[8]->IsActive)
				return Player->StoredBattleActors[8];
		return nullptr;
	case OBJ_Child9:
		if (IsPlayer && Player->StoredBattleActors[9])
			if (Player->StoredBattleActors[9]->IsActive)
				return Player->StoredBattleActors[9];
		return nullptr;
	case OBJ_Child10:
		if (IsPlayer && Player->StoredBattleActors[10])
			if (Player->StoredBattleActors[10]->IsActive)
				return Player->StoredBattleActors[10];
		return nullptr;
	case OBJ_Child11:
		if (IsPlayer && Player->StoredBattleActors[11])
			if (Player->StoredBattleActors[11]->IsActive)
				return Player->StoredBattleActors[11];
		return nullptr;
	case OBJ_Child12:
		if (IsPlayer && Player->StoredBattleActors[12])
			if (Player->StoredBattleActors[12]->IsActive)
				return Player->StoredBattleActors[12];
		return nullptr;
	case OBJ_Child13:
		if (IsPlayer && Player->StoredBattleActors[13])
			if (Player->StoredBattleActors[13]->IsActive)
				return Player->StoredBattleActors[13];
		return nullptr;
	case OBJ_Child14:
		if (IsPlayer && Player->StoredBattleActors[14])
			if (Player->StoredBattleActors[14]->IsActive)
				return Player->StoredBattleActors[14];
		return nullptr;
	case OBJ_Child15:
		if (IsPlayer && Player->StoredBattleActors[15])
			if (Player->StoredBattleActors[15]->IsActive)
				return Player->StoredBattleActors[15];
		return nullptr;
	default:
		return nullptr;
	}*/
	return nullptr;
}


