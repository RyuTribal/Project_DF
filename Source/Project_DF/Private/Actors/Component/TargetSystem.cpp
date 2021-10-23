#include "Actors/Component/TargetSystem.h"
#include "Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Components/ActorComponent.h"
#include "Actors/DF_Character.h"
#include "Components/WidgetComponent.h"

UTargetSystem::UTargetSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	MinimumDistanceToEnable = 1200.0f;
	ClosestTargetDistance = 0.0f;
	PitchDistanceCoefficient = -1.0f;
	bTargetLocked = false;
	LockedOnWidgetDrawSize = 32.0f;
	LockedOnWidgetRelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	BreakLineOfSightDelay = 2.0f;
	bIsBreakingLineOfSight = false;
	bShouldControlRotation = true;
	StartRotatingThreshold = 1.5f;
	StartRotatingStack = 0.0f;
	bIsSwitchingTarget = false;
	bShouldDrawLockedOnWidget = true;
	LockedOnWidgetParentSocket = FName("spine_03");
	bAdjustPitchBasedOnDistanceToTarget = true;
	bDesireToSwitch = false;
	AxisMultiplier = 1.0f;
	StickyRotationThreshold = 30.0f;
	CanTrack = false;

	TargetableActors = AActor::StaticClass();
}

// Called when the game starts
void UTargetSystem::BeginPlay()
{
	Super::BeginPlay();
	CharacterReference = GetOwner();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void UTargetSystem::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bTargetLocked && LockedOnTargetActor)
	{
		if (!TargetIsTargetable(LockedOnTargetActor))
		{
			TargetLockOff();
			return;
		}

		SetControlRotationOnTarget(LockedOnTargetActor);

		// Target Locked Off based on Distance
		if (GetDistanceFromCharacter(LockedOnTargetActor) > MinimumDistanceToEnable)
		{
			TargetLockOff();
			return;
		}

		if(!LockedOnTargetActor->GetActorEnableCollision())
		{
			TArray<AActor*> Actors = GetAllActorsOfClass(TargetableActors);
			TArray<AActor*> ActorsToLook;
			TArray<AActor*> ActorsToIgnore;
			for (AActor* Actor : Actors)
			{
				const bool bHit = LineTraceForActor(Actor, ActorsToIgnore);
				if (bHit && IsInViewport(Actor))
				{
					ActorsToLook.Add(Actor);
				}
			}
			TArray<AActor*> TargetsInRange = FindTargetsInRange(ActorsToLook, 0, 180);
			TargetLockOff();
			if (TargetsInRange.Num() != 0)
			{
				AActor* Nearest = FindNearestTarget(TargetsInRange);
				LockedOnTargetActor = Nearest;
				TargetLockOn(Nearest);
			}

		}

		if (ShouldBreakLineOfSight() && !bIsBreakingLineOfSight)
		{
			if (BreakLineOfSightDelay <= 0)
			{
				TargetLockOff();
			}
			else
			{
				bIsBreakingLineOfSight = true;
				GetWorld()->GetTimerManager().SetTimer(
					LineOfSightBreakTimerHandle,
					this,
					&UTargetSystem::BreakLineOfSight,
					BreakLineOfSightDelay
				);
			}
		}
		ADF_Character* Character = Cast<ADF_Character>(PlayerController->GetPawn());
		CanTrack = bTargetLocked && Character->IsEquipped && !Character->IsDodging && !Character->IsRunning && Character->CanTrack;
		AActor* Target = GetLockedOnTargetActor();
		if (CanTrack && !Target->GetActorRotation().Equals(Character->GetActorRotation()))
		{
			ControlRotation(false);
			Character->SetActorRotation(GetControlRotationOnTarget(Target));
		}
		else
		{
			ControlRotation(CanTrack);
		}
		
	}
}

void UTargetSystem::TargetActor()
{
	ClosestTargetDistance = MinimumDistanceToEnable;

	if (bTargetLocked)
	{
		TargetLockOff();
	}
	else
	{
		const TArray<AActor*> Actors = GetAllActorsOfClass(TargetableActors);
		LockedOnTargetActor = FindNearestTarget(Actors);
		TargetLockOn(LockedOnTargetActor);
	}
}

void UTargetSystem::TargetActorWithAxisInput(const float AxisValue)
{
	// If we're not locked on, do nothing
	if (!bTargetLocked)
	{
		return;
	}

	if (!LockedOnTargetActor)
	{
		return;
	}

	// If we're not allowed to switch target, do nothing
	if (!ShouldSwitchTargetActor(AxisValue))
	{
		return;
	}

	// If we're switching target, do nothing for a set amount of time
	if (bIsSwitchingTarget)
	{
		return;
	}

	// Lock off target
	AActor* CurrentTarget = LockedOnTargetActor;

	// Depending on Axis Value negative / positive, set Direction to Look for (negative: left, positive: right)
	const float RangeMin = AxisValue < 0 ? 0 : 180;
	const float RangeMax = AxisValue < 0 ? 180 : 360;

	// Reset Closest Target Distance to Minimum Distance to Enable
	ClosestTargetDistance = MinimumDistanceToEnable;

	// Get All Actors of Class
	TArray<AActor*> Actors = GetAllActorsOfClass(TargetableActors);

	// For each of these actors, check line trace and ignore Current Target and build the list of actors to look from
	TArray<AActor*> ActorsToLook;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(CurrentTarget);
	for (AActor* Actor : Actors)
	{
		const bool bHit = LineTraceForActor(Actor, ActorsToIgnore);
		if (bHit && IsInViewport(Actor))
		{
			ActorsToLook.Add(Actor);
		}
	}

	// Find Targets in Range (left or right, based on Character and CurrentTarget)
	TArray<AActor*> TargetsInRange = FindTargetsInRange(ActorsToLook, RangeMin, RangeMax);

	// For each of these targets in range, get the closest one to current target
	AActor* ActorToTarget = nullptr;
	for (AActor* Actor : TargetsInRange)
	{
		// and filter out any character too distant from minimum distance to enable
		const float Distance = GetDistanceFromCharacter(Actor);
		if (Distance < MinimumDistanceToEnable)
		{
			const float RelativeActorsDistance = CurrentTarget->GetDistanceTo(Actor);
			if (RelativeActorsDistance < ClosestTargetDistance)
			{
				ClosestTargetDistance = RelativeActorsDistance;
				ActorToTarget = Actor;
			}
		}
	}

	if (ActorToTarget)
	{
		if (SwitchingTargetTimerHandle.IsValid())
		{
			SwitchingTargetTimerHandle.Invalidate();
		}

		TargetLockOff();
		LockedOnTargetActor = ActorToTarget;
		TargetLockOn(ActorToTarget);

		GetWorld()->GetTimerManager().SetTimer(
			SwitchingTargetTimerHandle,
			this,
			&UTargetSystem::ResetIsSwitchingTarget,
			// Less sticky if still switching
			bIsSwitchingTarget ? 0.25f : 0.5f
		);
		bIsSwitchingTarget = true;
	}
}

AActor* UTargetSystem::GetLockedOnTargetActor() const
{
	return LockedOnTargetActor;
}

bool UTargetSystem::IsLocked() const
{
	return bTargetLocked && LockedOnTargetActor;
}

TArray<AActor*> UTargetSystem::FindTargetsInRange(TArray<AActor*> ActorsToLook, const float RangeMin, const float RangeMax) const
{
	TArray<AActor*> ActorsInRange;

	for (AActor* Actor : ActorsToLook)
	{
		const float Angle = GetAngleUsingCameraRotation(Actor);
		if (Angle > RangeMin && Angle < RangeMax)
		{
			ActorsInRange.Add(Actor);
		}
	}
	return ActorsInRange;
}

float UTargetSystem::GetAngleUsingCameraRotation(AActor* ActorToLook) const
{
	UCameraComponent* CameraComponent = CharacterReference->FindComponentByClass<UCameraComponent>();
	if (!CameraComponent)
	{
		// Fallback to CharacterRotation if no CameraComponent can be found
		return GetAngleUsingCharacterRotation(ActorToLook);
	}

	const FRotator CameraWorldRotation = CameraComponent->GetComponentRotation();
	const FRotator LookAtRotation = FindLookAtRotation(CameraComponent->GetComponentLocation(), ActorToLook->GetActorLocation());

	float YawAngle = CameraWorldRotation.Yaw - LookAtRotation.Yaw;
	if (YawAngle < 0)
	{
		YawAngle = YawAngle + 360;
	}
	return YawAngle;
}

float UTargetSystem::GetAngleUsingCharacterRotation(AActor* ActorToLook) const
{
	const FRotator CharacterRotation = CharacterReference->GetActorRotation();
	const FRotator LookAtRotation = FindLookAtRotation(CharacterReference->GetActorLocation(), ActorToLook->GetActorLocation());

	float YawAngle = CharacterRotation.Yaw - LookAtRotation.Yaw;
	if (YawAngle < 0)
	{
		YawAngle = YawAngle + 360;
	}
	return YawAngle;
}

FRotator UTargetSystem::FindLookAtRotation(const FVector Start, const FVector Target)
{
	return FRotationMatrix::MakeFromX(Target - Start).Rotator();
}

void UTargetSystem::ResetIsSwitchingTarget()
{
	bIsSwitchingTarget = false;
	bDesireToSwitch = false;
}

bool UTargetSystem::ShouldSwitchTargetActor(const float AxisValue)
{
	// Sticky feeling computation
	if (bEnableStickyTarget)
	{
		StartRotatingStack += (AxisValue != 0) ? AxisValue * AxisMultiplier : (StartRotatingStack > 0 ? -AxisMultiplier : AxisMultiplier);

		if (AxisValue == 0 && FMath::Abs(StartRotatingStack) <= AxisMultiplier)
		{
			StartRotatingStack = 0.0f;
		}

		// If Axis value does not exceeds configured threshold, do nothing
		if (FMath::Abs(StartRotatingStack) < StickyRotationThreshold)
		{
			bDesireToSwitch = false;
			return false;
		}

		//Sticky when switching target.
		if (StartRotatingStack * AxisValue > 0)
		{
			StartRotatingStack = StartRotatingStack > 0 ? StickyRotationThreshold : -StickyRotationThreshold;
		}
		else if (StartRotatingStack* AxisValue < 0)
		{
			StartRotatingStack = StartRotatingStack * -1.0f;
		}

		bDesireToSwitch = true;

		return true;
	}

	// Non Sticky feeling, check Axis value exceeds threshold
	return FMath::Abs(AxisValue) > StartRotatingThreshold;
}

void UTargetSystem::TargetLockOn(AActor* TargetToLockOn)
{
	if (TargetToLockOn)
	{
		bTargetLocked = true;
		if (bShouldDrawLockedOnWidget)
		{
			CreateAndAttachTargetLockedOnWidgetComponent(TargetToLockOn);
		}

		PlayerController->SetIgnoreLookInput(true);

		if (OnTargetLockedOn.IsBound())
		{
			OnTargetLockedOn.Broadcast(TargetToLockOn);
		}
	}
}

void UTargetSystem::TargetLockOff()
{
	bTargetLocked = false;
	if (TargetLockedOnWidgetComponent)
	{
		TargetLockedOnWidgetComponent->DestroyComponent();
	}

	if (LockedOnTargetActor)
	{

		PlayerController->ResetIgnoreLookInput();

		if (OnTargetLockedOff.IsBound())
		{
			OnTargetLockedOff.Broadcast(LockedOnTargetActor);
		}
	}

	LockedOnTargetActor = nullptr;
}

void UTargetSystem::CreateAndAttachTargetLockedOnWidgetComponent(AActor* TargetActor)
{
	TargetLockedOnWidgetComponent = NewObject<UWidgetComponent>(TargetActor, FName("TargetLockOn"));
	TargetLockedOnWidgetComponent->SetWidgetClass(LockedOnWidgetClass);

	UMeshComponent* MeshComponent = TargetActor->FindComponentByClass<UMeshComponent>();
	USceneComponent* ParentComponent = MeshComponent && LockedOnWidgetParentSocket != NAME_None ? MeshComponent : TargetActor->GetRootComponent();

	TargetLockedOnWidgetComponent->ComponentTags.Add(FName("TargetSystem.LockOnWidget"));
	TargetLockedOnWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	TargetLockedOnWidgetComponent->SetupAttachment(ParentComponent, LockedOnWidgetParentSocket);
	TargetLockedOnWidgetComponent->SetRelativeLocation(LockedOnWidgetRelativeLocation);
	TargetLockedOnWidgetComponent->SetDrawSize(FVector2D(LockedOnWidgetDrawSize, LockedOnWidgetDrawSize));
	TargetLockedOnWidgetComponent->SetVisibility(true);
	TargetLockedOnWidgetComponent->RegisterComponent();
}

TArray<AActor*> UTargetSystem::GetAllActorsOfClass(const TSubclassOf<AActor> ActorClass) const
{
	TArray<AActor*> Actors;
	for (TActorIterator<AActor> ActorIterator(GetWorld(), ActorClass); ActorIterator; ++ActorIterator)
	{
		AActor* Actor = *ActorIterator;
		const bool bIsTargetable = TargetIsTargetable(Actor);
		if (bIsTargetable)
		{
			Actors.Add(Actor);
		}
	}

	return Actors;
}

bool UTargetSystem::TargetIsTargetable(AActor* Actor)
{
	return true;
}

AActor* UTargetSystem::FindNearestTarget(TArray<AActor*> Actors) const
{
	TArray<AActor*> ActorsHit;

	// Find all actors we can line trace to
	for (AActor* Actor : Actors)
	{
		const bool bHit = LineTraceForActor(Actor);
		if (bHit && IsInViewport(Actor))
		{
			ActorsHit.Add(Actor);
		}
	}

	// From the hit actors, check distance and return the nearest
	if (ActorsHit.Num() == 0)
	{
		return nullptr;
	}

	float ClosestDistance = ClosestTargetDistance;
	AActor* Target = nullptr;
	for (AActor* Actor : ActorsHit)
	{
		const float Distance = GetDistanceFromCharacter(Actor);
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			Target = Actor;
		}
	}
	return Target;
}


bool UTargetSystem::LineTraceForActor(AActor* OtherActor, const TArray<AActor*> ActorsToIgnore) const
{
	FHitResult HitResult;
	const bool bHit = LineTrace(HitResult, OtherActor, ActorsToIgnore);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == OtherActor)
		{
			return true;
		}
	}
	return false;
}

bool UTargetSystem::LineTrace(FHitResult& HitResult, AActor* OtherActor, const TArray<AActor*> ActorsToIgnore) const
{
	FCollisionQueryParams Params = FCollisionQueryParams(FName("LineTraceSingle"));

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Init(CharacterReference, 1);
	IgnoredActors += ActorsToIgnore;

	Params.AddIgnoredActors(IgnoredActors);

	return GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CharacterReference->GetActorLocation(),
		OtherActor->GetActorLocation(),
		ECollisionChannel::ECC_Pawn,
		Params
	);
}

FRotator UTargetSystem::GetControlRotationOnTarget(AActor* OtherActor) const
{
	const FRotator ControlRotation = PlayerController->GetControlRotation();

	const FVector CharacterLocation = CharacterReference->GetActorLocation();
	const FVector OtherActorLocation = OtherActor->GetActorLocation();

	// Find look at rotation
	const FRotator LookRotation = FRotationMatrix::MakeFromX(OtherActorLocation - CharacterLocation).Rotator();

	float Pitch = LookRotation.Pitch;


	if (bAdjustPitchBasedOnDistanceToTarget)
	{
		const float DistanceToTarget = GetDistanceFromCharacter(OtherActor);
		const float PitchInRange = (DistanceToTarget * PitchDistanceCoefficient + PitchDistanceOffset) * -1.0f;
		const float PitchOffset = FMath::Clamp(PitchInRange, PitchMin, PitchMax);

		Pitch = Pitch + PitchOffset;
	}

	const FRotator TargetRotation = FRotator(Pitch, LookRotation.Yaw, ControlRotation.Roll);
	return FMath::RInterpTo(ControlRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
}

void UTargetSystem::SetControlRotationOnTarget(AActor* TargetActor) const
{
	if (!PlayerController)
	{
		return;
	}
	const FRotator ControlRotation = GetControlRotationOnTarget(TargetActor);
	if (OnTargetSetRotation.IsBound())
	{
		OnTargetSetRotation.Broadcast(TargetActor, ControlRotation);
	}
	else
	{
		FRotator NewRotation = FRotator(0, ControlRotation.Yaw, 0);
		PlayerController->SetControlRotation(NewRotation);
	}
}

float UTargetSystem::GetDistanceFromCharacter(AActor* OtherActor) const
{
	return CharacterReference->GetDistanceTo(OtherActor);
}

bool UTargetSystem::ShouldBreakLineOfSight() const
{
	if (!LockedOnTargetActor)
	{
		return true;
	}

	TArray<AActor*> ActorsToIgnore = GetAllActorsOfClass(TargetableActors);
	ActorsToIgnore.Remove(LockedOnTargetActor);

	FHitResult HitResult;
	const bool bHit = LineTrace(HitResult, LockedOnTargetActor, ActorsToIgnore);
	if (bHit && HitResult.GetActor() != LockedOnTargetActor)
	{
		return true;
	}
	return false;
}

void UTargetSystem::BreakLineOfSight()
{
	bIsBreakingLineOfSight = false;
	if (ShouldBreakLineOfSight())
	{
		TargetLockOff();
	}
}

void UTargetSystem::ControlRotation(const bool ShouldControlRotation) const
{
	APawn* Pawn = Cast<APawn>(CharacterReference);
	if (Pawn)
	{
		Pawn->bUseControllerRotationYaw = ShouldControlRotation;
	}

	UCharacterMovementComponent* CharacterMovementComponent = CharacterReference->FindComponentByClass<UCharacterMovementComponent>();
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->bOrientRotationToMovement = !ShouldControlRotation;
	}
}

bool UTargetSystem::IsInViewport(AActor* TargetActor) const
{
	if (!PlayerController)
	{
		return true;
	}

	FVector2D ScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(TargetActor->GetActorLocation(), ScreenLocation);

	FVector2D ViewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);

	return ScreenLocation.X > 0 && ScreenLocation.Y > 0 && ScreenLocation.X < ViewportSize.X&& ScreenLocation.Y < ViewportSize.Y;
}