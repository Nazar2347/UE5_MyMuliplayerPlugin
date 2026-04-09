// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MSP_SteamSessionsSubsystem.generated.h"

/**
 * Custom Delegates
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMSP_OnCreateSessionComplete, bool, bWasSuccceful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMSP_OnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionsResult, bool wasSuccefult);
DECLARE_MULTICAST_DELEGATE_OneParam(FMSP_OnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMSP_OnDestorySessionComplete, bool, bWasSucceful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMSP_OnStartSessionComplete, bool, bWasSucceful);

UCLASS()
class MYSTEAMMULTIPLAYERPLUGIN_API UMSP_SteamSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMSP_SteamSessionsSubsystem();
	
	//Custom Deleggates
	FMSP_OnCreateSessionComplete CustomOnCreateSessionCompleteDelegate;
	FMSP_OnFindSessionsComplete CustomOnFindSessionsCompleteDelegate;
	FMSP_OnJoinSessionComplete CustomOnJoinSessionCompleteDelegate;
	FMSP_OnDestorySessionComplete CustomOnDestroySessionCompleteDelegate;
	FMSP_OnStartSessionComplete CustomOnStartSessionCompleteDelegate;
	
	
	void CreateSession(int32 NumberOfPlayers, FString MatchType);
	void FindSession(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);
	void DestroySession();
	void StartSession();
	
protected:
	//Callbacks for Delegates 
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnStartSessionComplete(FName SessionName, bool Success);
private:
	bool bCreateSessionOnDestroy {false};
	int32 LastNumberOfPlayers;
	FString LastMatchType;
	
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
	TSharedPtr<FOnlineSessionSearch>LastSessionSearch;
	
	
	//Delegates for OnlineSessionInterface
	
	//Create
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	//Find
	FOnFindSessionsCompleteDelegate FindSessionCompleteDelegate;
	FDelegateHandle FindSessionCompleteDelegateHandle;
	//Join
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
	//Destroy
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;
	//Start
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;
	
};
