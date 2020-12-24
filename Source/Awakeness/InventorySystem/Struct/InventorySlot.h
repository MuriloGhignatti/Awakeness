#pragma once

#include "../MasterClass/MasterItem/MasterItem.h"
#include "GenericPlatform/GenericPlatform.h"
#include "InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	AMasterItem* ItemClass;
	int32 Amount;
};