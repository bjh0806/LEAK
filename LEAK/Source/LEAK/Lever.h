// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "Lever.generated.h"


UCLASS()
class LEAK_API ALever : public ASkeletalMeshActor
{
	GENERATED_BODY()
public:
	ALever();

	void LeverDown();
};
