// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamSessionsSubsystem.h"

#include "OnlineSubsystem.h"


USteamSessionsSubsystem::USteamSessionsSubsystem():
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

void USteamSessionsSubsystem::CreateSession(int32 NumberOfPlayers, FString MatchType)
{
}

void USteamSessionsSubsystem::FindSession(int32 MaxSearchResults)
{
}

void USteamSessionsSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
}

void USteamSessionsSubsystem::DestroySession()
{
}

void USteamSessionsSubsystem::StartSession()
{
}

void USteamSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool Success)
{
}

void USteamSessionsSubsystem::OnFindSessionComplete(bool Success)
{
}

void USteamSessionsSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void USteamSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool Success)
{
}

void USteamSessionsSubsystem::OnStartSessionComplete(FName SessionName, bool Success)
{
}
