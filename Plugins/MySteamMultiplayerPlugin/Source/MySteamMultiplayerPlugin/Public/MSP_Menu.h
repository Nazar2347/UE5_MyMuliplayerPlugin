// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSP_Menu.generated.h"

/**
 * 
 */
UCLASS()
class MYSTEAMMULTIPLAYERPLUGIN_API UMSP_Menu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();
	
	
	
};
