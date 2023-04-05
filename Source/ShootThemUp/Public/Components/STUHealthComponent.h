// Shoot Them Up Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    USTUHealthComponent();

    float GetHealth() const
    {
        return Health;
    }

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;

    // Called when the game starts
    virtual void BeginPlay() override;

  private:
    float Health = 0.0f;
};
