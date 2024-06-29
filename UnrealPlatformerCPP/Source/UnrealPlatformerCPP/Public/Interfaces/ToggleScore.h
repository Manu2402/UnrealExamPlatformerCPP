// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToggleScore.generated.h"

UINTERFACE(MinimalAPI)
class UToggleScore : public UInterface
{
	GENERATED_BODY()
};

class UNREALPLATFORMERCPP_API IToggleScore
{
	GENERATED_BODY()

public:
	void ToggleScore(int32 Score);

};
