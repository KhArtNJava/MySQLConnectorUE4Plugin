using UnrealBuildTool;
using System.IO;

public class MySQLConnectorUE4Plugin : ModuleRules
{
    public MySQLConnectorUE4Plugin(ReadOnlyTargetRules Target) : base(Target)
    {
        //File.WriteAllText("c:/temp/qqq.txt", this.GetType().Name);
        //string ModulePath = Path.GetDirectoryName( RulesAssembly.GetModuleFilename( this.GetType().Name ) );

        //UEBuildConfiguration.bForceEnableExceptions = true;

        RulesAssembly r;
        FileReference CheckProjectFile;
	// replace the String with your Project name!!!
        UProjectInfo.TryGetProjectForTarget("AR_rev_v_curr", out CheckProjectFile);

        r = RulesCompiler.CreateProjectRulesAssembly(CheckProjectFile);
        FileReference f = r.GetModuleFileName(this.GetType().Name);
        //File.WriteAllText("c:/temp/qqq2.txt", f.CanonicalName );		
        string ModulePath = Path.GetDirectoryName(f.CanonicalName);
        string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
        string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));
        string LibrariesPath = Path.Combine(ThirdPartyPath, "MySQLConnector", "Lib");
        string LibraryName = Path.Combine(LibrariesPath, "mariadbclient." + PlatformString + ".lib");



        PublicAdditionalLibraries.Add(LibraryName);

        PrivateIncludePaths.AddRange(new string[] {
            "MySQLConnectorUE4Plugin/Private"
        });

        string IncludesPath = Path.Combine(ThirdPartyPath, "MySQLConnector", "Include");
        string IncludesPath2 = Path.Combine(ThirdPartyPath, "MySQLConnector", "Include", "cppconn");

        PublicIncludePaths.AddRange(new string[] {
            "MySQLConnectorUE4Plugin/Public",
            IncludesPath,
            IncludesPath2
        });




        PublicDependencyModuleNames.AddRange(new string[] {
            "Engine",
            "Core",
            "CoreUObject"
        });
    }
}