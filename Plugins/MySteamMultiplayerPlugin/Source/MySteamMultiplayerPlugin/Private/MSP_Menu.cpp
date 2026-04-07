// Fill out your copyright notice in the Description page of Project Settings.


#include "MSP_Menu.h"


void UMSP_Menu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;
	
	if (TObjectPtr<UWorld> World = GetWorld())
	{
		if (TObjectPtr<APlayerController> PlayerController = World->GetFirstPlayerController())
		{
			//Configuring Input for Widget
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}
