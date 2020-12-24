// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEmpty.h"

AItemEmpty::AItemEmpty()
{
    Id = -1;
    
    ItemInfo.Name = FText::FromString("Empty");
    ItemInfo.Description = FText::FromString("Empty Slot");
    ItemInfo.UseText = FText::FromString("Can't use Empty Slot");
    ItemInfo.Weight = -1.0F;
    ItemInfo.ItemCategory = Empty;
    ItemInfo.Usable = false;
    ItemInfo.Stackable = false;
    ItemInfo.Icon = nullptr;
    ItemInfo.PickupMesh = nullptr;
    ItemInfo.MeshScale = FVector(0,0,0);
    ItemInfo.MeshPosition = FVector(0,0,0);
    ItemInfo.BoxCollisionScale = FVector(0,0,0);
    ItemInfo.Radius = 0.0F;
    ItemInfo.HalfHeight = 0.0F;
}

