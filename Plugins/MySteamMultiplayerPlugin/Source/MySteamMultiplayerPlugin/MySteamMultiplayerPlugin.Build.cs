// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MySteamMultiplayerPlugin : ModuleRules
{
	public MySteamMultiplayerPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				//Menu Widgets compatability
				"UMG",
				"Slate",
				"SlateCore",
				//Online Subsystem Steam
				"OnlineSubsystem",
				"OnlineSubsystemSteam",
				"OnlineSubsystemUtils",
				"SteamSockets"
				
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// Required for UE 5.6 for Steam Sockets
				"OnlineServicesInterface",
				"OnlineServicesCommon",
				"OnlineServicesOSSAdapter"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
				
			}
			);
	}
}
