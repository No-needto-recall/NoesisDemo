using UnrealBuildTool;

public class NoesisViewMode : ModuleRules
{
    public NoesisViewMode(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "GameplayTags", 
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore",
                "UMG",
                "Noesis",
                "NoesisRuntime",
                "Json",
                "JsonUtilities",
            }
        );

        PublicIncludePaths.AddRange(
            new string[] 
            {
                // 添加公共头文件路径
            }
        );

        PrivateIncludePaths.AddRange(
            new string[]
            {
                // 添加私有头文件路径
            }
        );
    }
}