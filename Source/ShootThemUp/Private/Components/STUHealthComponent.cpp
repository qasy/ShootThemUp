// Shoot Them Up Game

#include "Components/STUHealthComponent.h"
#include <GameFramework/Actor.h>

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
    Health = MaxHealth;

    AActor *ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        GetOwner()->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
    }
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                                                class AController *InstigatedBy, AActor *DamageCauser)
{
    Health -= Damage;
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %0.1f"), Damage);
}
