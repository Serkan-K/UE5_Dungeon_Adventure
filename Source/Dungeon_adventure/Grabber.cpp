// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



UGrabber::UGrabber()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//UPhysicsHandleComponent* phys_Handle = Get_phys_Handle();
	//phys_Handle = nullptr;
	//if (phys_Handle != nullptr)
	//{
	//	UE_LOG(LogTemp, Display, TEXT("phys geldi: %s "), *phys_Handle->GetName());
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("no Phys handle!"));
	//}
}





void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* phys_Handle = Get_phys_Handle();




	if (phys_Handle && phys_Handle->GetGrabbedComponent() != nullptr)
	{
		FVector hold_ = GetComponentLocation() + GetForwardVector() * Hold_dist;
		phys_Handle->SetTargetLocationAndRotation(hold_, GetComponentRotation());
	}
}












void UGrabber::Grab()
{
#pragma region Rotate_info

	//FRotator m_rotation = GetComponentRotation();
	//FString Rot_string = m_rotation.ToCompactString();

	//UE_LOG(LogTemp, Warning, TEXT("Grabber rotation:  %s"), *Rot_string);


	//float time_ = GetWorld()->TimeSeconds;
#pragma endregion


	UPhysicsHandleComponent* phys_Handle =
		GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (phys_Handle == nullptr) { return; }

	FHitResult hit_res;
	bool has_Hit = In_grab(hit_res);

	if (has_Hit)
	{
		//DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 10, 10, FColor::Orange, false, 2);
		//AActor* hit_Actor = hit_result.GetActor();
		//UE_LOG(LogTemp, Warning, TEXT("Hit actor name: %s"), *hit_Actor->GetActorNameOrLabel());

		UPrimitiveComponent* hit_comp = hit_res.GetComponent();
		hit_comp->SetSimulatePhysics(true);
		hit_comp->WakeAllRigidBodies();
		AActor* hit_Actor = hit_res.GetActor();
		hit_Actor->Tags.Add("Grabbed");
		hit_Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		phys_Handle
			->GrabComponentAtLocationWithRotation(hit_comp, NAME_None, hit_res.ImpactPoint, GetComponentRotation());

	}
	//else {
	//	UE_LOG(LogTemp, Display, TEXT("No actor"));
	//}


#pragma region Ref_vs_Point

	//float damage_;
	////float& damage_ref = damage_;
	////damage_ref = 5;

	//if (Has_Damage(damage_))
	//{
	//	Print_Damage(damage_);
	//}

	////UE_LOG(LogTemp, Display, TEXT("Damage Ref: %f, Damage: %f"), damage_ref, damage_);

#pragma endregion

}










void UGrabber::Release()
{
	UPhysicsHandleComponent* phys_handle_ = Get_phys_Handle();


	if (phys_handle_ && phys_handle_->GetGrabbedComponent())
	{
		AActor* grabbed_actor = phys_handle_->GetGrabbedComponent()->GetOwner();
		grabbed_actor->Tags.Remove("Grabbed");

		phys_handle_->ReleaseComponent();
	}
}















UPhysicsHandleComponent* UGrabber::Get_phys_Handle() const
{
	UPhysicsHandleComponent* result_ = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (result_ == nullptr) { UE_LOG(LogTemp, Error, TEXT("Grabber require Phys Handle")); }
	return result_;
}



bool UGrabber::In_grab(FHitResult& Out_hit_res) const
{
	FVector start_ = GetComponentLocation();
	FVector end_ = start_ + GetForwardVector() * max_Grab_dist;

	/*DrawDebugLine(GetWorld(), start_, end_, FColor::Cyan);
	DrawDebugSphere(GetWorld(), end_, 15, 10, FColor::Magenta, false, 1);*/

	FCollisionShape sphere_ = FCollisionShape::MakeSphere(grap_Radius);

	return GetWorld()->SweepSingleByChannel(
		Out_hit_res, start_, end_,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		sphere_);
}






//void UGrabber::Print_Damage(const float& Dmg)
//{
//	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), Dmg);
//}
//
//bool UGrabber::Has_Damage(float& out_Dmg)
//{
//	out_Dmg = 5;
//	return true;
//}

