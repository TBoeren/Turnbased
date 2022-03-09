// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "AbilityDataTableStruct.generated.h"

UENUM(BlueprintType)
enum class EAbilityAnimationTypes: uint8
{
    Idle     UMETA(DisplayName = "Idle"),
    AttackW      UMETA(DisplayName = "Attack (Weapon)"),
    AttackP      UMETA(DisplayName = "Attack (Punch)"),
    Spell      UMETA(DisplayName = "Spell"),
    ReceiveHit      UMETA(DisplayName = "Receive Hit"),
    Death      UMETA(DisplayName = "Death"),
};

UENUM(BlueprintType)
enum class ETeamEnum : uint8
{
    OwnTeam     UMETA(DisplayName = "OwnTeam"),
    OtherTeam      UMETA(DisplayName = "OtherTeam"),
};

UENUM(BlueprintType)
enum class EAbilityTargets: uint8
{
    Self     UMETA(DisplayName = "Self"),
    Target     UMETA(DisplayName = "Target"),
};

UENUM(BlueprintType)
enum class EAbilityEffects: uint8
{
    Damage     UMETA(DisplayName = "Damage"),
    Healing     UMETA(DisplayName = "Healing"),
    DOT     UMETA(DisplayName = "DOT"),
    Debuff     UMETA(DisplayName = "Debuff"),
    Buff     UMETA(DisplayName = "Buff"),
    Move     UMETA(DisplayName = "Move"),
    Cure     UMETA(DisplayName = "Cure"),
};

UENUM(BlueprintType)
enum class EDeBuffType: uint8
{
    None     UMETA(DisplayName = "None"),
    Blindness     UMETA(DisplayName = "Blindness"),
    Dodge50     UMETA(DisplayName = "Dodge (50%)"),
    Dodge75     UMETA(DisplayName = "Dodge (75%)"),
    DamageUp50     UMETA(DisplayName = "Damage Increased (50%)"),
};

UENUM(BlueprintType)
enum class EDOTType: uint8
{
    None     UMETA(DisplayName = "None"),
    Poison     UMETA(DisplayName = "Poison"),
    Burn     UMETA(DisplayName = "Burn"),
    Bleed     UMETA(DisplayName = "Bleed"),
};

UENUM(BlueprintType)
enum class ETargetStat: uint8
{
    Health     UMETA(DisplayName = "Health"),
    DOT     UMETA(DisplayName = "DOT"),
    DeBuff     UMETA(DisplayName = "(De)Buff"),
};

UENUM(BlueprintType)
enum class EOperator: uint8
{
    Greater     UMETA(DisplayName = ">"),
    GreaterEqual     UMETA(DisplayName = ">="),
    Equal     UMETA(DisplayName = "=="),
    LessEqual     UMETA(DisplayName = "<="),
    Less     UMETA(DisplayName = "<"),
};

USTRUCT(BlueprintType)
struct FAIAbilityModifierStruct
{
    GENERATED_BODY();

    FAIAbilityModifierStruct()        
    {
        
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ETargetStat TargetStat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "TargetStat == ETargetStat::Health"))
        EOperator Operator;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "TargetStat == ETargetStat::Health"))
        int Percentage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "TargetStat == ETargetStat::DOT"))
        EDOTType DOTType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "TargetStat == ETargetStat::DeBuff"))
        EAbilityTargets AbilityTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "TargetStat == ETargetStat::DeBuff"))
        EDeBuffType DeBuffType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int ExtraScore;
};

USTRUCT(BlueprintType)
struct FAbilityEffectStruct
{
    GENERATED_BODY();

    FAbilityEffectStruct()        
    {
        
    }

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        EAbilityTargets AbilityTarget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        EAbilityEffects AbilityEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::Damage || AbilityEffects == EAbilityEffects::Healing"))
        FInt32Range AbilityPowerRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::Debuff || AbilityEffects == EAbilityEffects::Buff"))
        EDeBuffType DeBuffType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::Debuff || AbilityEffects == EAbilityEffects::Buff"))
        int DeBuffStacks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::DOT"))
        EDOTType DOTType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::DOT"))
        int DOTStrength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::DOT"))
        int DOTDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::Move"))
        int MoveDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::Cure"))
        EDOTType CureType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "AbilityEffects == EAbilityEffects::Cure"))
        EDeBuffType CureDeBuffType;
};

USTRUCT(BlueprintType)
struct FAbilityStruct : public FTableRowBase
{
    GENERATED_BODY();

    FAbilityStruct()        
    {

    }

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        UTexture2D* Thumbnail;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        FText AbilityName;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        FText AbilityDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        EAbilityAnimationTypes AnimationType;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        ETeamEnum TargetTeam;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        bool TargetSelfOnly;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        TArray<int> AbilityPositions;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite, meta = (EditCondition = "!TargetSelfOnly"))
        TArray<int> TargetPositions = {0,1,2,3};

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        bool HitAllPossibleTargets;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        bool HasCooldown;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite, meta = (EditCondition = "HasCooldown"))
        bool OnCooldown;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite, meta = (EditCondition = "HasCooldown"))
        int CooldownDuration;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite, meta = (EditCondition = "HasCooldown"))
        int CurrentCooldown;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        TArray<FAbilityEffectStruct> AbilityEffects;

    UPROPERTY(EditAnywhere ,BlueprintReadWrite)
        TArray<FAIAbilityModifierStruct> AIAbilityModifiers;
};
