// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterItem.h"

#include <algorithm>

// Sets default values
AMasterItem::AMasterItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
{
	Super::BeginPlay();
	Id = Hash();
}

// Called every frame
void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AMasterItem::Hash()
{
	int32 Result = 0;
	FString Name = ItemInfo.Name.ToString();
	FString Description = ItemInfo.Description.ToString();
	FString UseText = ItemInfo.UseText.ToString();
	int ForVar = std::max(Name.Len(), Description.Len());
	ForVar = std::max(ForVar, UseText.Len());
	for(int i = 0; i < ForVar; i++)
	{
		if(i < Name.Len())
			Result += i * Name[i];
		if(i < Description.Len())
			Result += i * Description[i];
		if(i < UseText.Len())
			Result += i * UseText[i];
	}

	Result += ItemInfo.Weight * 3;

	Result += ItemInfo.ItemCategory.GetValue() * 3;

	Result += ItemInfo.Usable ? 3 : 0;

	Result += ItemInfo.Stackable ? 3 : 0;

	if(ItemInfo.PickupMesh != nullptr)
		Result += ItemInfo.Icon->GetUniqueID();

	if(ItemInfo.PickupMesh != nullptr)
		Result += ItemInfo.PickupMesh->GetUniqueID();

	Result += ItemInfo.MeshScale.X * 3 + ItemInfo.MeshScale.Y * 3 + ItemInfo.MeshScale.Z * 3;

	Result += ItemInfo.MeshPosition.X * 3 + ItemInfo.MeshPosition.Y * 3 + ItemInfo.MeshPosition.Z * 3;

	Result += ItemInfo.BoxCollisionScale.X * 3 + ItemInfo.BoxCollisionScale.Y * 3 + ItemInfo.BoxCollisionScale.Z * 3;

	Result += ItemInfo.Radius * 3;

	Result += ItemInfo.HalfHeight * 3;

	return Result;
}




// void AMasterItem::OnUse()
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("You %s %s"), ToCStr(ItemInfo.UseText.ToString()), ToCStr(ItemInfo.Name.ToString())));
// }
