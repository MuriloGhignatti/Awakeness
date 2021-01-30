// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterInventory.h"

// Sets default values
AMasterInventory::AMasterInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SlotsInited = true;
}

// Called when the game starts or when spawned
void AMasterInventory::BeginPlay()
{
	Super::BeginPlay();
	InitSlots();
}

// Called every frame
void AMasterInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMasterInventory::IsSlotEmpty(const int32 Index)
{
	return Slots[Index].ItemClass == nullptr;
}

FItemInfo AMasterInventory::GetItemInfoAtIndex(const int32 Index, int32& Amount, bool& IsEmpty)
{
	IsEmpty = false;
	if(IsSlotEmpty(Index))
	{
		IsEmpty = true;
		return FItemInfo{};
	}
	Amount = Slots[Index].Amount;
	return Slots[Index].ItemClass->ItemInfo;
}

int32 AMasterInventory::SearchEmptySlot()
{
	for(size_t i = 0; i < Slots.Num(); i++)
		if(IsSlotEmpty(i))
			return i;
	
	return INDEX_NONE;
}

int32 AMasterInventory::SearchFreeStack(TSubclassOf<class AMasterItem> ItemClass)
{
	for(short i = 0; i < Slots.Num(); i++)
		if(!IsSlotEmpty(i) && Slots[i].ItemClass->Id == ItemClass.GetDefaultObject()->Id && Slots[i].Amount < MaxStackSize)
			return i;
	
	return INDEX_NONE;
}

int32 AMasterInventory::AddItem(TSubclassOf<class AMasterItem> ItemClass, const int32 Amount)
{
	int FoundIndex = INDEX_NONE;
	if(ItemClass.GetDefaultObject()->ItemInfo.Stackable)
	{
		if((FoundIndex = SearchFreeStack(ItemClass)) != INDEX_NONE)
		{
			if((Slots[FoundIndex].Amount + Amount) > MaxStackSize)
			{
				Slots[FoundIndex].Amount = MaxStackSize;
				UpdateSlotWidget(FoundIndex);
				return AddItem(ItemClass, Amount - MaxStackSize);
			}
			else
			{
				Slots[FoundIndex].Amount += Amount;
				UpdateSlotWidget(FoundIndex);
				return 0;
			}
		}
		else
		{
			if((FoundIndex = SearchEmptySlot()) != INDEX_NONE)
			{
				if(Amount > MaxStackSize)
				{
					Slots[FoundIndex] = FInventorySlot{NewObject<AMasterItem>(ItemClass, ItemClass), MaxStackSize};
					UpdateSlotWidget(FoundIndex);
					return AddItem(ItemClass, Amount - MaxStackSize);
				}
				else
				{
					Slots[FoundIndex] = FInventorySlot{NewObject<AMasterItem>(ItemClass, ItemClass), Amount};
					UpdateSlotWidget(FoundIndex);
					return 0;
				}
			}
			else
				return -1;
		}
	}
	else
	{
		if((FoundIndex = SearchEmptySlot()) != INDEX_NONE)
		{
			Slots[FoundIndex] = FInventorySlot{NewObject<AMasterItem>(ItemClass, ItemClass), 1};
			UpdateSlotWidget(FoundIndex);
			if(Amount > 1)
				return AddItem(ItemClass, Amount - 1);
			else
				return 0;
		}
		else
			return -1;
	}
}

int32 AMasterInventory::GetAmountAtIndex(const int32 Index)
{
	return Slots[Index].Amount;
}

bool AMasterInventory::RemoveItemAtIndex(const int32 Index, const int32 Amount)
{
	if(Slots[Index].Amount <= Amount)
	{
		Slots[Index].ItemClass = nullptr;
		UpdateSlotWidget(Index);
		return true;
	}
	else if(Slots[Index].Amount == Amount)
	{
		Slots[Index].ItemClass = nullptr;
		UpdateSlotWidget(Index);
		return true;
	}
	else
	{
		Slots[Index].Amount -= Amount;
		UpdateSlotWidget(Index);
		return true;
	}
}

bool AMasterInventory::SwapSlots(const int32 Index1, const int32 Index2)
{
	FInventorySlot Holder = Slots[Index1];
	Slots[Index1] = Slots[Index2];
	UpdateSlotWidget(Index1);
	Slots[Index2] = Holder;
	UpdateSlotWidget(Index2);
	return true;
}

bool AMasterInventory::SplitStack(const int32 Index, const int32 Amount)
{
	if(Slots[Index].Amount > Amount && Slots[Index].ItemClass->ItemInfo.Stackable)
	{
		int Found = SearchEmptySlot();
		if(Found != INDEX_NONE)
		{
			Slots[Index].Amount -= Amount;
			Slots[Found] = FInventorySlot{Slots[Index].ItemClass, Amount};
			UpdateSlotWidget(Index);
			return true;
		}
		return false;
	}
	return false;
}

bool AMasterInventory::UseItemAtIndex(const int32 Index, const int32 Amount)
{
	if(IsSlotEmpty(Index))
		return false;
	
	Slots[Index].ItemClass->OnUse(Amount);
	RemoveItemAtIndex(Index, Amount);
	return true;
}



