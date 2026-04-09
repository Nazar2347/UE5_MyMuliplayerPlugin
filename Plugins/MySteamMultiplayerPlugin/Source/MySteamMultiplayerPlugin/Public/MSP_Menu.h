// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MSP_Menu.generated.h"

/**
 * 
 */
UCLASS()
class MYSTEAMMULTIPLAYERPLUGIN_API UMSP_Menu : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPlayers = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString LobbyPath = FString(TEXT("/Game/ThirdPerson/Lvl_ThirdPerson")));
	
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;
	
	int32 NumPublicConnections{4};
	FString MatchType {FString("FreeForAll")};
	FString PathToSessionMap {TEXT("")};
	
	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();
	
	void TurnOffMenu();
	
	class UMSP_SteamSessionsSubsystem* MultiplayerSessionSubsystem;
	
	
	
	
protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	
	//Callbacks for my own SteamSubsytem
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& Sessions, bool Successful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnAbandomSession(bool Success);
	UFUNCTION()
	void OnLaunchSession(bool Success);
};
