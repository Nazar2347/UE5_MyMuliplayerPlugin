// Fill out your copyright notice in the Description page of Project Settings.


#include "MSP_SteamSessionsSubsystem.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"


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
	LastSessionSettings->bUsesPresence = true;
	LastSessionSettings->Set(FName("MatchType"),MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	const TObjectPtr<ULocalPlayer> LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);
	}
	
	 
	
}

void UMSP_SteamSessionsSubsystem::FindSession(int32 MaxSearchResults)
{
}

void UMSP_SteamSessionsSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
}

void UMSP_SteamSessionsSubsystem::DestroySession()
{
}

void UMSP_SteamSessionsSubsystem::StartSession()
{
}

void UMSP_SteamSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool Success)
{
}

void UMSP_SteamSessionsSubsystem::OnFindSessionComplete(bool Success)
{
}

void UMSP_SteamSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UMSP_SteamSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool Success)
{
}

void UMSP_SteamSessionsSubsystem::OnStartSessionComplete(FName SessionName, bool Success)
{
}
