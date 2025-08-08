using UnrealBuildTool;

public class SimpleShooter : ModuleRules
{
	public SimpleShooter(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(["Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"]);

		PrivateDependencyModuleNames.AddRange([]);

		PublicDependencyModuleNames.AddRange(["AIModule"]);

	}
}
