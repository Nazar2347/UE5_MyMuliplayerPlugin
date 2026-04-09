// Fill out your copyright notice in the Description page of Project Settings.


#include "MSP_SteamSessionsSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Online/OnlineSessionNames.h"


UMSP_SteamSessionsSubsystem::UMSP_SteamSessionsSubsystem():
	//Binding callbacks to Delegates
	CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this,&ThisClass::OnCreateSessionComplete)),
	FindSessionCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this,&ThisClass::OnFindSessionComplete)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionComplete))

{
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
	
}

void UMSP_SteamSessionsSubsystem::CreateSession(int32 NumberOfPlayers, FString MatchType)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	//Cheking if a session already exists
	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession); // if  exists - then destroy
	}
	//Store Delegate in Delegate Handle for managment
	CreateSessionCompleteDelegateHandle = SessionInterface ->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true:false; //if no Steam Subsystem is On
	LastSessionSettings->NumPublicConnections = NumberOfPlayers;
	LastSessionSettings->bAllowJoinInProgress =true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bShouldAdvertise = true;
	LastSessionSettings->bUseLobbiesIfAvailable = true;
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->Set(FName("MatchType"),MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	const TObjectPtr<ULocalPlayer> LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
		//Broadcast to own deleagte
		CustomOnCreateSessionCompleteDelegate.Broadcast(false);
	}
}

void UMSP_SteamSessionsSubsystem::FindSession(int32 MaxSearchResults)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	FindSessionCompleteDelegateHandle =SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegate);
	LastSessionSearch= MakeShareable(new FOnlineSessionSearch());
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	LastSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true:false;
	LastSessionSearch->QuerySettings.Set(SEARCH_LOBBIES,true,EOnlineComparisonOp::Equals);
	
	const TObjectPtr<ULocalPlayer> LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(),LastSessionSearch.ToSharedRef()))
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);
		//Broadcast to Menu
		CustomOnFindSessionsCompleteDelegate.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
	}
	else
	{
		
	}
	
	
}

void UMSP_SteamSessionsSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
	if (!SessionInterface.IsValid())
	{
		CustomOnJoinSessionCompleteDelegate.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		return;
	}
	JoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);
	
	const TObjectPtr<ULocalPlayer> LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(),NAME_GameSession, SessionResult))
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		CustomOnJoinSessionCompleteDelegate.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
		
	}
	
}

void UMSP_SteamSessionsSubsystem::DestroySession()
{
}

void UMSP_SteamSessionsSubsystem::StartSession()
{
	
}

void UMSP_SteamSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool Success)
{
	//remove delegate from list
	if (SessionInterface)
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
	
	CustomOnCreateSessionCompleteDelegate.Broadcast(Success);
}

void UMSP_SteamSessionsSubsystem::OnFindSessionComplete(bool Success)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionCompleteDelegateHandle);
	}
	
	if (LastSessionSearch->SearchResults.Num() <= 0)
	{
		CustomOnFindSessionsCompleteDelegate.Broadcast(LastSessionSearch->SearchResults, false);
		return;
	}
	
	CustomOnFindSessionsCompleteDelegate.Broadcast(LastSessionSearch->SearchResults, Success);
}

void UMSP_SteamSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (SessionInterface)
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
	}
	CustomOnJoinSessionCompleteDelegate.Broadcast(Result);
}

void UMSP_SteamSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool Success)
{
}

void UMSP_SteamSessionsSubsystem::OnStartSessionComplete(FName SessionName, bool Success)
{
}
