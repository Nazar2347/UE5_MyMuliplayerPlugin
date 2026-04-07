// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamSessionsSubsystem.h"

#include "OnlineSubsystem.h"


USteamSessionsSubsystem::USteamSessionsSubsystem()
{
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
	
}
