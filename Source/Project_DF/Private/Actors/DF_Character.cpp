// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DF_Character.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Actors/Component/TargetSystem.h"
#include "DrawDebugHelpers.h"
// Sets default values
ADF_Character::ADF_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init the capsule by setting the radius and half height of it
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	DefaultJump = CreateDefaultSubobject<UAnimMontage>(TEXT("DefaultJump"));
	DefaultHitReaction = CreateDefaultSubobject<UAnimMontage>(TEXT("DefaultHitReaction"));
	DefaultDeath = CreateDefaultSubobject<UAnimMontage>(TEXT("DefaultDeath"));

	AbilitySystemComponent = CreateDefaultSubobject<UDF_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	

	// Remove the mouse restrictions on the camera (mouse moves camera not the character)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	// How far he jumps
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->GravityScale = 2.8f;

	// Sets the spring to the arm component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	CameraBoom->SocketOffset = FVector(-160.f, 0.f, 50.f);

	CameraBoom->TargetArmLength = 300.0f; // The length of which the camera is from the player
	CameraBoom->bUsePawnControlRotation = true; // Mouse moves the arm that is attached to camera

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false; // Mouse does not move the actual camera

	CanMove = true;
	IsDodging = false;
	IsMoving = false;
	IsLocked = false;
	DodgeDistance = 2500.0f;
	CanEnterIdle = true;
	JogSpeed = 600.f;
	SprintSpeed = 1000.f;
	IsRunning = false;
	IsEquipped = false;
	IsSheathing = false;
	CurrentAttack = 0;
	CanAttack = true;
	CanTrack = true;
	IsFalling = false;
	IsDead = false;

	FAxis = 0.f;
	RAxis = 0.f;
	ShowFloatingHealth = ESlateVisibility::Hidden;
	IsLockedOn = false;
}

// Our construction script
void ADF_Character::OnConstruction(const FTransform& Transform)
{
}

void ADF_Character::GetHealthValues(float& Health, float& MaxHealth)
{
	Health = Attributes->GetHealth();
	MaxHealth = Attributes->GetMaxHealth();
}

void ADF_Character::GetStaminaValues(float& Stamina, float& MaxStamina)
{
	Stamina = Attributes->GetStamina();
	MaxStamina = Attributes->GetMaxStamina();
}

void ADF_Character::GetSinValues(float& Sinmeter, float& MaxSinmeter)
{
	Sinmeter = Attributes->GetSinmeter();
	MaxSinmeter = Attributes->GetMaxSinmeter();
}

UAbilitySystemComponent* ADF_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ADF_Character::OnTargetLockedOn(AActor* TargetActor)
{
	ADF_Character* Target = Cast<ADF_Character>(TargetActor);
	Target->ShowFloatingHealth = ESlateVisibility::Visible;
	Target->IsLockedOn = true;
	IsLocked = true;
	
}

void ADF_Character::OnTargetLockedOff(AActor* TargetActor)
{
	ADF_Character* Target = Cast<ADF_Character>(TargetActor);
	Target->ShowFloatingHealth = ESlateVisibility::Hidden;
	Target->IsLockedOn = false;
	IsLocked = false;
}

void ADF_Character::HideHealthBar()
{
	if(!IsLockedOn)
	{
		ShowFloatingHealth = ESlateVisibility::Hidden;
	}
}

void ADF_Character::GiveStartingAbilities()
{
	if(AbilitySystemComponent && InputComponent)
	{
		for(TSubclassOf<UDF_GameplayAbility>& StartupAbility : DefaultAbilities)
		{
			if (IsValid(StartupAbility))
			{
				FGameplayAbilitySpec Spec = FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this);
				AbilitySystemComponent->GiveAbility(Spec);
				if (StartupAbility.GetDefaultObject()->IsPassive)
				{
					AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
				}
			}
		}
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGASAbilityInputID", static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ADF_Character::GiveStartingEffects()
{
	if (AbilitySystemComponent && DefaultEffects.Num() != 0)
	{
		FGameplayEffectContextHandle EffectHandle = AbilitySystemComponent->MakeEffectContext();
		EffectHandle.AddSourceObject(this);
		for (TSubclassOf<UGameplayEffect>& StartupEffect : DefaultEffects)
		{
			FGameplayEffectSpecHandle DefaultEffectHandle = AbilitySystemComponent->MakeOutgoingSpec(StartupEffect, 1, EffectHandle);
			if(DefaultEffectHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveEffect = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DefaultEffectHandle.Data.Get());
			}
		}
		
	}
}

void ADF_Character::AddGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect)
{
	if (AbilitySystemComponent && IsValid(Effect))
	{
		FGameplayEffectContextHandle EffectHandle = AbilitySystemComponent->MakeEffectContext();
		EffectHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle DefaultEffectHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectHandle);
		if (DefaultEffectHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveEffect = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DefaultEffectHandle.Data.Get());
		}

	}
}

// Called when the game starts or when spawned
void ADF_Character::BeginPlay()
{
	Super::BeginPlay();

	if (Weapon)
	{
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		AWeaponBase* PlayerWeapon = GetWorld()->SpawnActor<AWeaponBase>(Weapon, Location, Rotation, SpawnInfo);
		PlayerWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("greatsword-sheathe"));
		WeaponPtr = PlayerWeapon;
	}
	if(IsValid(AbilitySystemComponent))
	{
		Attributes = AbilitySystemComponent->GetSet<UDF_AttributeSet>();
		GiveStartingAbilities();
		GiveStartingEffects();
	}

	UTargetSystem* TargetSystem = FindComponentByClass<UTargetSystem>();
	if(IsValid(TargetSystem))
	{
		TargetSystem->OnTargetLockedOn.AddDynamic(this, &ADF_Character::OnTargetLockedOn);
		TargetSystem->OnTargetLockedOff.AddDynamic(this, &ADF_Character::OnTargetLockedOff);
	}
}

float ADF_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	/*if (Damage) {
		GetMesh()->GetAnimInstance()->Montage_Play(DefaultDeath);
		this->SetCanBeDamaged(false);
		IsDead = true;
		FOnMontageEnded BlendOutDelegate;
		BlendOutDelegate.BindUObject(this, &ADF_Character::OnDeath);
		GetMesh()->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDelegate, DefaultDeath);
	}
	else {*/
	if(DamageCauser->GetInstigatorController() && ShowFloatingHealth != ESlateVisibility::Visible)
	{
		GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
		ShowFloatingHealth = ESlateVisibility::Visible;
		FTimerDelegate HealthDelegateHandle;
		HealthDelegateHandle.BindUFunction(this, FName("HideHealthBar"));
		GetWorldTimerManager().SetTimer(HealthTimerHandle, HealthDelegateHandle, 1.0f, false);
	}
	GetMesh()->GetAnimInstance()->Montage_Play(DefaultHitReaction);

	//}
	
	return 0.0f;
}

void ADF_Character::OnDeath(UAnimMontage* animMontage, bool bInterrupted)
{
	if(!IsPlayerControlled())
	{
		this->GetMesh()->SetSimulatePhysics(true);
	}
	
}

void ADF_Character::Falling()
{
	if (!IsDodging && !IsFalling)
	{
		IsFalling = true;
		GetController()->SetIgnoreMoveInput(true);
		GetMesh()->GetAnimInstance()->RootMotionMode = ERootMotionMode::IgnoreRootMotion;
		if (IsEquipped && WeaponPtr)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(WeaponPtr->Jump);
		}
		else
		{
			GetMesh()->GetAnimInstance()->Montage_Play(DefaultJump);
		}
	}
}

void ADF_Character::Landed(const FHitResult& Hit)
{
	if (IsFalling)
	{
		IsFalling = false;
		GetController()->SetIgnoreMoveInput(false);
		GetMesh()->GetAnimInstance()->RootMotionMode = ERootMotionMode::RootMotionFromMontagesOnly;
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(FName("Jump_End"), GetMesh()->GetAnimInstance()->GetCurrentActiveMontage());
	}
}

// Called every frame
void ADF_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADF_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// For camera movement
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// These axis commands are always fired at tick. Very important to remember
	PlayerInputComponent->BindAxis("MoveForward", this, &ADF_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADF_Character::MoveRight);

	// different inputs
	//PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &ADF_Character::Dodge);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ADF_Character::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ADF_Character::Jog);
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ADF_Character::HandleEquip);
	PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &ADF_Character::LightAttack);
	PlayerInputComponent->BindAction("TargetLock", IE_Pressed, this, &ADF_Character::TargetLockPressed);
}

void ADF_Character::MoveForward(float Axis)
{
	FAxis = Axis;
	if(CanMove)
	{
		HandleChangeMovement();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector FDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(FDirection, Axis);
	}
}

void ADF_Character::MoveRight(float Axis)
{
	RAxis = Axis;
	if (CanMove)
	{
		HandleChangeMovement();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector RDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RDirection, Axis);
		
	}
}

void ADF_Character::TargetLockPressed()
{
	UTargetSystem* TargetSystem = FindComponentByClass<UTargetSystem>();
	TargetSystem->TargetActor();
}

void ADF_Character::HandleChangeMovement()
{
	UCharacterMovementComponent* cMove = GetCharacterMovement();
	if (cMove->Velocity.Size() == 0.f) //If the character is still
	{
		IsMoving = false;
	}
	else
	{
		IsMoving = true;
	}
}

void ADF_Character::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	IsRunning = true;
}

void ADF_Character::Jog()
{
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	IsRunning = false;
}

void ADF_Character::HandleEquip()
{
	/*
	 * Animations are taken from the weapon
	 */
	UAnimInstance* Animations = GetMesh()->GetAnimInstance();

	if (!Animations->IsAnyMontagePlaying()) {
		if (IsEquipped && WeaponPtr) {
			if (!IsSheathing) {
				IsEquipped = false;
				IsSheathing = true;
				
				Animations->Montage_Play(WeaponPtr->Sheathe, 1.f);
				FOnMontageEnded CompleteDelegate;
				CompleteDelegate.BindUObject(this, &ADF_Character::OnEquipInterrupt);
				Animations->Montage_SetEndDelegate(CompleteDelegate, WeaponPtr->Sheathe);
			}
		}
		else {
			if (!IsSheathing) {
				IsEquipped = true;
				IsSheathing = true;
				EquippedWeapon = WeaponPtr->id;
				Animations->Montage_Play(WeaponPtr->UnSheathe, 1.f);
				FOnMontageEnded CompleteDelegate;
				CompleteDelegate.BindUObject(this, &ADF_Character::OnEquipInterrupt);
				Animations->Montage_SetEndDelegate(CompleteDelegate, WeaponPtr->UnSheathe);
			}
		}
	}
}

void ADF_Character::OnEquipInterrupt(UAnimMontage* animMontage, bool bInterrupted)
{
	if(IsEquipped && WeaponPtr)
	{
		WeaponPtr->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("right_hand_equip"));
	}
	else
	{
		WeaponPtr->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("greatsword-sheathe"));
	}
	IsSheathing = false;
}

FRotator ADF_Character::GetDesiredRotation()
{
	if(HadMovementInput())
	{
		return UKismetMathLibrary::MakeRotFromX(GetLastMovementInputVector());
	}
	else
	{
		return GetActorRotation();
	}
		
}

bool ADF_Character::HadMovementInput()
{
	return !GetLastMovementInputVector().Equals(FVector(0.f, 0.f, 0.f));
}

/*
 * Attack functions
 */
void ADF_Character::LightAttack()
{

	UAnimInstance* Animations = GetMesh()->GetAnimInstance(); // To be able to handle animations
	/*
	* If Can attack then plays the start attack
	*/
	if(CanAttack)
	{
		if(IsRunning)
		{
			Animations->Montage_Play(WeaponPtr->RunningAttack);
		}
		else if(IsDodging)
		{
			Animations->Montage_Play(WeaponPtr->DodgeAttack);
		}
		else
		{
			StartAttack();
		}
		
	}
	else
	{
		if(Animations->Montage_IsPlaying(WeaponPtr->AttackCombo)) //Checks that the montage is the attack combo
		{
			/*
			 * This chunk checks that the combo is currently in the
			 * "ComboWindow" state. You can check the attack combo montage to see
			 * how the animations are sectioned.
			 */
			
			FString CurrentSectionPlaying = Animations->Montage_GetCurrentSection(WeaponPtr->AttackCombo).ToString();
			FString ReferenceSection = TEXT("ComboWindow_");
			ReferenceSection.AppendInt(CurrentAttack);
			if(CurrentSectionPlaying.Equals(ReferenceSection))
			{
				//Skips to the next attack so that it doesn't play the end of an attack.
				FString NextSection = TEXT("Attack_");
				CurrentAttack = CurrentAttack + 1;
				if(CurrentAttack > WeaponPtr->AmmountLightAttacks)
				{
					CurrentAttack = 1;
				}
				NextSection.AppendInt(CurrentAttack);
				Animations->Montage_JumpToSection(FName(NextSection), Animations->GetCurrentActiveMontage());
			}

		}
	}
}



void ADF_Character::StartAttack()
{
	UAnimInstance* Animations = GetMesh()->GetAnimInstance(); // To be able to handle animations
	/*
	 * If the weapon is unequiped, this adds the weapon
	 * to the socket instantly and changes state to
	 * equipped so that the player isn't animation
	 * locked.
	 */
	
	if (!IsEquipped)
	{
		IsEquipped = true;
		WeaponPtr->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("right_hand_equip"));

	}
	CanTrack = false;
	IsAttacking = true;
	CanAttack = false;
	CurrentAttack = 1;
	Animations->Montage_Play(WeaponPtr->AttackCombo, 1.f); //Plays the attack montage from the start
	FOnMontageEnded BlendOutDelegate;
	BlendOutDelegate.BindUObject(this, &ADF_Character::OnAttackCompleting);
	Animations->Montage_SetBlendingOutDelegate(BlendOutDelegate, WeaponPtr->AttackCombo); //Since it blends out (smoother transitions) I put a function to handle ending of the combo
}

void ADF_Character::OnAttackCompleting(UAnimMontage* animMontage, bool bInterrupted)
{
	IsAttacking = false;
	CanAttack = true;
	CurrentAttack = 0;
	CanTrack = true;
}