#pragma once

#include "../Enum/ItemCategory.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"
#include "Math/Float32.h"
#include "Math/Vector.h"
#include "ItemInfo.generated.h"

USTRUCT(BlueprintType, Meta = (InstanceEditable = "true"))
struct FItemInfo
{
public:
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText UseText;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Weight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EItemCategory> ItemCategory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Usable;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Stackable;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;
    
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* PickupMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector MeshScale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector MeshPosition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector BoxCollisionScale;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Radius;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HalfHeight;
};