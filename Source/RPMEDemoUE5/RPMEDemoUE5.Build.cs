// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RPMEDemoUE5 : ModuleRules
{
	public RPMEDemoUE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        PrivateDependencyModuleNames.AddRange(new string[] { "ReadyPlayerMe" });

        // Dependencies Web Browser
        PrivateDependencyModuleNames.AddRange(new string[] { "WebBrowserWidget", "WebBrowser", "UMG" });
    }
}
