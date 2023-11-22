// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class LEAK_API AExitDoor : public ASkeletalMeshActor
{
	GENERATED_BODY()
public:
	AExitDoor();

	void CurFloor(int levelname);
private:
	bool open{};
	enum floorname {
		B2, B1, floor, final
	};
	int NextFloor{0};
};
