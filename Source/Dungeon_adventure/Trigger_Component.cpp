// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger_Component.h"


UTrigger_Component::UTrigger_Component()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UTrigger_Component::BeginPlay()
{
	Super::BeginPlay();
}

void UTrigger_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* _actor = get_Key();

	if (_actor != nullptr)
	{

		UPrimitiveComponent* component_ = Cast<UPrimitiveComponent>(_actor->GetRootComponent());
		if (component_ != nullptr)
		{
			component_->SetSimulatePhysics(false);
		}
		_actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		_actor->SetActorRelativeRotation(FRotator::ZeroRotator);

		Mover->Should_Move(true);
	}
	else { Mover->Should_Move(false); }
}








void UTrigger_Component::Set_Mover(UMover* Mover_)
{
	Mover = Mover_;
}



AActor* UTrigger_Component::get_Key() const
{

	TArray<AActor*> actors_array;
	GetOverlappingActors(actors_array);


	for (AActor* actor_ : actors_array)
	{
		bool tagged_ = actor_->ActorHasTag(tag_name);
		bool Is_Grabbed = actor_->ActorHasTag("Grabbed");

		if (tagged_ && !Is_Grabbed)
		{
			return actor_;
		}
	}
	return nullptr;
}
