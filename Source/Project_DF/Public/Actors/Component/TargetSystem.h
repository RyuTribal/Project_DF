#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/WidgetComponent.h"
#include "TargetSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FComponentOnTargetLockedOnOff, AActor*, TargetActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComponentSetRotation, AActor*, TargetActor, FRotator, ControlRotation);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_DF_API UTargetSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetSystem();

	// The minimum distance to enable target locked on.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
		float MinimumDistanceToEnable;

	// The AActor Subclass to search for targetable Actors.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
		TSubclassOf<AActor> TargetableActors;

	// Whether or not the character rotation should be controlled when Target is locked on.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
		bool bShouldControlRotation;

	// The amount of time to break line of sight when actor gets behind an Object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
		float BreakLineOfSightDelay;

	// Switch new target on right or left.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System")
		float StartRotatingThreshold;

	// Whether or not the Target LockOn Widget indicator should be drawn and attached automatically.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
		bool bShouldDrawLockedOnWidget;

	// The Widget Class to use when locked on Target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
		TSubclassOf<UUserWidget> LockedOnWidgetClass;

	// The Widget Draw Size for the Widget class to use when locked on Target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
		float LockedOnWidgetDrawSize;

	// The Socket name to attach the LockedOn Widget.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
		FName LockedOnWidgetParentSocket;

	// The Relative Location to apply on Target LockedOn Widget when attached to a target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Widget")
		FVector LockedOnWidgetRelativeLocation;

	// Adjust the Pitch Offset (the Y axis) when locked on, depending on the distance to the target actor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
		bool bAdjustPitchBasedOnDistanceToTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
		float PitchDistanceCoefficient = -0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
		float PitchDistanceOffset = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
		float PitchMin = -50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
		float PitchMax = -20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Sticky Feeling on Target Switch")
		bool bEnableStickyTarget;

	// This value gets multiplied to the AxisValue to check against StickyRotationThreshold.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Sticky Feeling on Target Switch")
		float AxisMultiplier;

	// Switch new target on right or left.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Sticky Feeling on Target Switch")
		float StickyRotationThreshold;

	// Function to call to target a new actor.
	UFUNCTION(BlueprintCallable, Category = "Target System")
		void TargetActor();

	// Function to call to manually untarget.
	UFUNCTION(BlueprintCallable, Category = "Target System")
		void TargetLockOff();

	UFUNCTION(BlueprintCallable, Category = "Target System")
		void TargetActorWithAxisInput(float AxisValue);

	// Called when a target is locked off, either if it is out of reach (based on MinimumDistanceToEnable) or behind an Object.
	UPROPERTY(BlueprintAssignable, Category = "Target System")
		FComponentOnTargetLockedOnOff OnTargetLockedOff;

	// Called when a target is locked on
	UPROPERTY(BlueprintAssignable, Category = "Target System")
		FComponentOnTargetLockedOnOff OnTargetLockedOn;

	// Setup the control rotation on Tick when a target is locked on.
	UPROPERTY(BlueprintAssignable, Category = "Target System")
		FComponentSetRotation OnTargetSetRotation;

	//// Returns the reference to currently targeted Actor if any
	UFUNCTION(BlueprintCallable, Category = "Target System")
		AActor* GetLockedOnTargetActor() const;

	//// Returns true / false whether the system is targeting an actor
	UFUNCTION(BlueprintCallable, Category = "Target System")
		bool IsLocked() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target System|Pitch Offset")
		bool bTargetLocked;
	void ControlRotation(bool ShouldControlRotation) const;

private:
	UPROPERTY()
		AActor* CharacterReference;

	UPROPERTY()
		APlayerController* PlayerController;

	UPROPERTY()
		AActor* LockedOnTargetActor;

	UPROPERTY()
		UWidgetComponent* TargetLockedOnWidgetComponent;

	FTimerHandle LineOfSightBreakTimerHandle;
	FTimerHandle SwitchingTargetTimerHandle;

	bool bIsBreakingLineOfSight;
	bool bIsSwitchingTarget;
	float ClosestTargetDistance;

	bool bDesireToSwitch;
	float StartRotatingStack;

	// Actors search / trace
	TArray<AActor*> GetAllActorsOfClass(TSubclassOf<AActor> ActorClass) const;
	TArray<AActor*> FindTargetsInRange(TArray<AActor*> ActorsToLook, float RangeMin, float RangeMax) const;

	AActor* FindNearestTarget(TArray<AActor*> Actors) const;

	bool LineTrace(FHitResult& HitResult, AActor* OtherActor, TArray<AActor*> ActorsToIgnore = TArray<AActor*>()) const;
	bool LineTraceForActor(AActor* OtherActor, TArray<AActor*> ActorsToIgnore = TArray<AActor*>()) const;

	bool ShouldBreakLineOfSight() const;
	void BreakLineOfSight();

	bool IsInViewport(AActor* TargetActor) const;

	float GetDistanceFromCharacter(AActor* OtherActor) const;


	// Actor rotation
	FRotator GetControlRotationOnTarget(AActor* OtherActor) const;
	void SetControlRotationOnTarget(AActor* TargetActor) const;

	float GetAngleUsingCameraRotation(AActor* ActorToLook) const;
	float GetAngleUsingCharacterRotation(AActor* ActorToLook) const;

	static FRotator FindLookAtRotation(const FVector Start, const FVector Target);

	// Widget
	void CreateAndAttachTargetLockedOnWidgetComponent(AActor* TargetActor);

	// Targeting
	void TargetLockOn(AActor* TargetToLockOn);
	void ResetIsSwitchingTarget();
	bool ShouldSwitchTargetActor(float AxisValue);

	static bool TargetIsTargetable(AActor* Actor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};