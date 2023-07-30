using UnrealBuildTool;

public class LEAKTarget : TargetRules
{
	public LEAKTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.V2;
		Type = TargetType.Game;
		ExtraModuleNames.Add("LEAK");
	}
}
