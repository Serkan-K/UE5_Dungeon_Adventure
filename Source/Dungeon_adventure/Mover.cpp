// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	org_Loc = GetOwner()->GetActorLocation();

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector target_Loc = org_Loc;
	if (IsMove)
	{
		target_Loc = org_Loc + move_Offset;
	}

	FVector Curr_Loc = GetOwner()->GetActorLocation();
	float _speed = move_Offset.Length() / move_time;


	FVector new_Loc =
		FMath::VInterpConstantTo(Curr_Loc, target_Loc, DeltaTime, _speed);

	GetOwner()->SetActorLocation(new_Loc);


#pragma region Pointer exp



	//AActor* Owner = GetOwner();
	////FString _Name = (*Owner).GetActorNameOrLabel();
	//FString _Name = Owner->GetActorNameOrLabel();

	//FVector Owner_loc = Owner->GetActorLocation();
	//FString Owner_loc_string = Owner_loc.ToCompactString();

	//UE_LOG(LogTemp, Warning, TEXT("Mover Owner %s with %s "), *_Name, *Owner_loc_string);

	//-------------------------------------------------------------------------------------------------------------------------------

	//float m_float = 8;
	//float* y_float = &m_float;
	//float float_val = *y_float;
	//UE_LOG(LogTemp, Display, TEXT("ikinci floata atanan deger % f"), float_val);
	//UE_LOG(LogTemp, Display, TEXT("ikinci floata atanan deger % f"), *y_float);
#pragma endregion

}



void UMover::Should_Move(bool Is_Move_)
{
	IsMove = Is_Move_;
}
