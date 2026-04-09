// Fill out your copyright notice in the Description page of Project Settings.


#include "MSP_Menu.h"

#include "Components/Button.h"
#include "MSP_SteamSessionsSubsystem.h"
#include "OnlineSessionSettings.h"

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

void UMSP_Menu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,
				FString(TEXT("Session was created succefully")));
		}
		if (TObjectPtr<UWorld> World = GetWorld())
		{
			World->ServerTravel("/Game/ThirdPerson/Lvl_ThirdPerson?listen");
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,
				FString(TEXT("Session failed to create")));
		}
	}
}

void UMSP_Menu::OnFindSession(const TArray<FOnlineSessionSearchResult>& Sessions, bool Successful)
{
	if (MultiplayerSessionSubsystem == nullptr)
	{
		return;
	}
	for (auto SearchResult : Sessions)
	{
		FString SettingValue;
		SearchResult.Session.SessionSettings.Get(FName("MatchType"), SettingValue);
		
		FString Id = SearchResult.GetSessionIdStr();
		FString User = SearchResult.Session.OwningUserName;
		int32 NumOfPlayers = SearchResult.Session.NumOpenPublicConnections;
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Blue,
				FString::Printf(TEXT("Id: %s, User: %s PlayerCount: %i" ),*Id, *User, NumOfPlayers)
				);
		}
		if (SettingValue == MatchType)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Cyan,
				FString::Printf(TEXT("Joining Match Type %s of Player %s "),*MatchType, *User)
				);
			}
			MultiplayerSessionSubsystem->JoinSession(SearchResult);
			return;
		}
		
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Red,
		FString(TEXT("No matching sessions were found!"))
		);
	}
}

void UMSP_Menu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address ;
			SessionInterface->GetResolvedConnectString(NAME_GameSession,Address);
			
			TObjectPtr<APlayerController> PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address,TRAVEL_Absolute);
			}
		}
			
	}
}

void UMSP_Menu::OnAbandomSession(bool Success)
{
}

void UMSP_Menu::OnLaunchSession(bool Success)
{
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
	
	//Bind Callbacks
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CustomOnCreateSessionCompleteDelegate.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionSubsystem->CustomOnFindSessionsCompleteDelegate.AddUObject(this, &ThisClass::OnFindSession);
		MultiplayerSessionSubsystem->CustomOnJoinSessionCompleteDelegate.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionSubsystem->CustomOnDestroySessionCompleteDelegate.AddDynamic(this, &ThisClass::OnAbandomSession);
		MultiplayerSessionSubsystem->CustomOnStartSessionCompleteDelegate.AddDynamic(this, &ThisClass::OnLaunchSession);
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
	}
}

void UMSP_Menu::JoinButtonClicked()
{
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->FindSession(10000);
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
