#pragma once

#include "ItemCategory.generated.h"

UENUM(BlueprintType)
enum EItemCategory
{
	Weapon,
    Tool,
    Resource,
    Construction,
    Item,
    Empty,
};