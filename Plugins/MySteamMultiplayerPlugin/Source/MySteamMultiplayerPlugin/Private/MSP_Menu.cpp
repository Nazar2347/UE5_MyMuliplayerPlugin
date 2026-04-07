// Fill out your copyright notice in the Description page of Project Settings.


#include "MSP_Menu.h"

#include "Components/Button.h"
#include "MSP_SteamSessionsSubsystem.h"

bool UMSP_Menu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked); // Bind onClicked Event
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);// Bind onClicked Event
	}
	
	return true;
}

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
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMSP_SteamSessionsSubsystem>();
	}
}

void UMSP_Menu::HostButtonClicked()
{
	if (GEngine)
	{
			GEngine->AddOnScreenDebugMessage
			(-1, 15.f,FColor::Yellow,
			FString(TEXT("HostButtonClicked"))
			);
	}
	
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(8,FString("FreeForAll"));
	}
}

void UMSP_Menu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage
			(-1, 15.f,FColor::Yellow,
			FString(TEXT("JoinButtonClicked"))
			);
	}
	
}
