// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MPTest1 : ModuleRules
{
	public MPTest1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			//-- Multiplayer
			"OnlineSubsystem",
			"OnlineSubsystemSteam",
			"OnlineSubsystemUtils",
			"SteamSockets",
          
			// --- UE 5.6 ADAPTER FIXES ---
			"OnlineServicesInterface",
			"OnlineServicesCommon",
			"OnlineServicesOSSAdapter"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MPTest1",
			"MPTest1/Variant_Platforming",
			"MPTest1/Variant_Platforming/Animation",
			"MPTest1/Variant_Combat",
			"MPTest1/Variant_Combat/AI",
			"MPTest1/Variant_Combat/Animation",
			"MPTest1/Variant_Combat/Gameplay",
			"MPTest1/Variant_Combat/Interfaces",
			"MPTest1/Variant_Combat/UI",
			"MPTest1/Variant_SideScrolling",
			"MPTest1/Variant_SideScrolling/AI",
			"MPTest1/Variant_SideScrolling/Gameplay",
			"MPTest1/Variant_SideScrolling/Interfaces",
			"MPTest1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
	

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
