// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GameState)
	{
		int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
		
		if (APlayerState* NewPlayerState = NewPlayer->GetPlayerState<APlayerState>())
		{
			FString NewPlayerName= NewPlayerState->GetPlayerName();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,
					FString::Printf(TEXT("Player: %s  joined the game!"),*NewPlayerName ));
			}
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,
				FString::Printf(TEXT("Players in session: %d"), NumOfPlayers));
		}
	}
}

void ALobbyGameMode::Logout(AController* ExitingPlayer)
{
	Super::Logout(ExitingPlayer);
	
	if (GameState)
	{
		int32 NumOfPlayers = GameState.Get()->PlayerArray.Num();
		
		if (APlayerState* NewPlayerState = ExitingPlayer->GetPlayerState<APlayerState>())
		{
			FString NewPlayerName= NewPlayerState->GetPlayerName();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Orange,
					FString::Printf(TEXT("Player : %s  left the game"),*NewPlayerName ));
			}
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Cyan,
				FString::Printf(TEXT("Players in session: %d"), NumOfPlayers-1));
		}
	}
	
}
