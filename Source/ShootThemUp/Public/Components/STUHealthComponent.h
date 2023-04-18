// Shoot Them Up Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

    UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class SHOOTTHEMUP_API USTUHealthComponent
    : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    USTUHealthComponent();

    float GetHealth() const
    {
        return Health;
    }

    UFUNCTION(BlueprintCallable)
    bool IsDead() const
    {
        return FMath::IsNearlyZero(Health);
    }

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

    // Called when the game starts
    virtual void BeginPlay() override;

  private:
    float Health = 0.0f;
    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                               class AController *InstigatedBy, AActor *DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);
};
