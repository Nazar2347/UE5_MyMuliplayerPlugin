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

void UMSP_Menu::NativeDestruct()
{
	TurnOffMenu();
	Super::NativeDestruct();
}

void UMSP_Menu::MenuSetup(int32 NumOfPlayers, FString TypeOfMatch)
{
	NumPublicConnections = NumOfPlayers;
	MatchType = TypeOfMatch;
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
			(-1, 3.f,FColor::Yellow,
			FString(TEXT("HostButtonClicked"))
			);
	}
	
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
		if (TObjectPtr<UWorld> World = GetWorld())
		{
			World->ServerTravel("/Game/ThirdPerson/Lvl_ThirdPerson?listen");
		}
	}
}

void UMSP_Menu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage
			(-1, 3.f,FColor::Yellow,
			FString(TEXT("JoinButtonClicked"))
			);
	}
	
}

void UMSP_Menu::TurnOffMenu()
{
	RemoveFromParent(); //Remove the widget
	if (TObjectPtr<UWorld> World = GetWorld())
	{
		if (TObjectPtr<APlayerController> PlayerController = World->GetFirstPlayerController())
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData); // Enable Input for game
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
