# MPTest1

Developed with Unreal Engine 5


## Plugins to include with this plugin:
  -OnlineSubsystem-Steam

## Stuff to add in DefaultEngine.ini:
  #---- Online Subsystem Steam ----
  
[/Script/Engine.GameEngine]
!NetDriverDefinitions=ClearArray
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/SteamSockets.SteamSocketsNetDriver",DriverClassNameFallback="/Script/OnlineSubsystemUtils.IpNetDriver") 

[OnlineSubsystem]
DefaultPlatformService=Steam
 
[OnlineSubsystemSteam]
bEnabled=true
SteamDevAppId=480
bInitServerOnClient=true
bUsesPresence=true
bUseLobbiesIfAvailable=true
bAllowP2PPacketRelay=true
bUseSteamNetworking=true
 
[/Script/SteamSockets.SteamSocketsNetDriver]
NetConnectionClassName="SteamSockets.SteamSocketsNetConnection"

[PacketHandlerComponents]
+Components=OnlineSubsystemSteam.SteamAuthComponentModuleInterface

#----------------------------------

## Stuff to add in DefaultGame.ini:

#--------------------------------

[/Script/Engine.GameSession]
MaxPlayers =16

#--------------------------------
