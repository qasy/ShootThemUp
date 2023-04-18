// Shoot Them Up Game

#include "Components/STUHealthComponent.h"
// #include <Dev/STUFireDamageType.h>
// #include <Dev/STUIceDamageType.h>
#include <Engine/World.h>
#include <GameFramework/Actor.h>
#include <TimerManager.h>

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)
// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
    // features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHealth(MaxHealth);

    AActor *ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        GetOwner()->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
    }
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                                                class AController *InstigatedBy, AActor *DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
    {
        return;
    }

    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal || GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime,
                                               true, HealDelay);
    }

    // UE_LOG(LogHealthComponent, Display, TEXT("Damage: %0.1f from %s"), Damage, *DamageCauser->GetName());

    // if (DamageType)
    //{
    //     if (DamageType->IsA<USTUFireDamageType>())
    //     {
    //         UE_LOG(LogHealthComponent, Display, TEXT("Fire Damage"));
    //     }

    //    else if (DamageType->IsA<USTUIceDamageType>())
    //    {
    //        UE_LOG(LogHealthComponent, Display, TEXT("Ice Damage"));
    //    }
    //}
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
