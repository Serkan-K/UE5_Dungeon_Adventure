// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEON_ADVENTURE_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void Grab();
	UFUNCTION(BlueprintCallable)
	void Release();


private:
	UPROPERTY(EditAnywhere)
	float max_Grab_dist = 400;

	UPROPERTY(EditAnywhere)
	float grap_Radius = 100;

	UPROPERTY(EditAnywhere)
	float Hold_dist = 200;

	UPhysicsHandleComponent* Get_phys_Handle() const;

	bool In_grab(FHitResult& Out_hit_res) const;


	//void Print_Damage(const float& Damage_);
	//bool Has_Damage(float& out_Damage);

};