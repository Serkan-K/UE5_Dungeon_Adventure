// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "Trigger_Component.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEON_ADVENTURE_API UTrigger_Component : public UBoxComponent
{
	GENERATED_BODY()


public:
	// Sets default values for this component's properties
	UTrigger_Component();

protected:
	virtual void BeginPlay() override;


public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Set_Mover(UMover* Mover);





private:
	UPROPERTY(EditAnywhere)
	FName tag_name;

	UMover* Mover;

	AActor* get_Key() const;

};
