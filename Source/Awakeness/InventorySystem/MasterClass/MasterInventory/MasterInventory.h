// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Containers/Array.h"
#include "GenericPlatform/GenericPlatform.h"
#include "../../Struct/InventorySlot.h"
#include "../../Items/ItemEmpty/ItemEmpty.h"
#include "MasterInventory.generated.h"

UCLASS(Blueprintable)
class AWAKENESS_API AMasterInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterInventory();

	UPROPERTY(BlueprintReadWrite, BlueprintGetter=GetSlotsInited)
	bool SlotsInited = false;
	
	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	int32 AmountOfSlots = 21;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	int32 AmountOfSlotsInHotbar = 5;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 MaxStackSize = 9999;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FInventorySlot> Slots;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSlotEmpty(const int32 Index);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemInfo GetItemInfoAtIndex(const int32 Index, int32& Amount, bool& IsEmpty);
	UFUNCTION(BlueprintCallable)
	int32 SearchEmptySlot();
	UFUNCTION(BlueprintCallable)
	int32 SearchFreeStack(TSubclassOf<class AMasterItem> ItemClass);
	UFUNCTION(BlueprintCallable)
	int32 AddItem(TSubclassOf<class AMasterItem> ItemClass, const int32 Amount);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetAmountAtIndex(const int32 Index);
	UFUNCTION(BlueprintCallable)
	bool RemoveItemAtIndex(const int32 Index, const int32 Amount);
	UFUNCTION(BlueprintCallable)
	bool SwapSlots(const int32 Index1, const int32 Index2);
	UFUNCTION(BlueprintCallable)
	bool SplitStack(const int32 Index, const int32 Amount);
	UFUNCTION(BlueprintCallable)
	bool UseItemAtIndex(const int32 Index, const int32 Amount);

	UFUNCTION(BlueprintImplementableEvent)
    void UpdateSlotWidget(int32 Index);

	UFUNCTION(BlueprintGetter)
	TArray<FInventorySlot> GetSlots()
	{
		if(!SlotsInited)
		{
			InitSlots();
		}
		return Slots;
	}

	UFUNCTION(BlueprintCallable)
	void InitSlots()
	{
		if(!SlotsInited)
		{
			Slots.Init(FInventorySlot{nullptr, 0}, (AmountOfSlots + AmountOfSlotsInHotbar) + 1);
			SlotsInited = true;
		}
	}
	
	UFUNCTION(BlueprintGetter)
	bool GetSlotsInited()
	{
		return SlotsInited;
	}

	UFUNCTION(BlueprintGetter)
	int32 GetSlotsSize()
	{
		return Slots.Num();
	}
	
};
