using UnrealBuildTool;
using System.IO;

public class MySQLConnectorUE4Plugin : ModuleRules
{
    public MySQLConnectorUE4Plugin(TargetInfo Target)
    {
        //File.WriteAllText("c:/temp/qqq.txt", this.GetType().Name);
        //string ModulePath = Path.GetDirectoryName( RulesAssembly.GetModuleFilename( this.GetType().Name ) );

        UEBuildConfiguration.bForceEnableExceptions = true;

        RulesAssembly r;
		FileReference CheckProjectFile;
		UProjectInfo.TryGetProjectForTarget("MyGame", out CheckProjectFile);
		
		r = RulesCompiler.CreateProjectRulesAssembly(CheckProjectFile);
		FileReference f = r.GetModuleFileName( this.GetType().Name );
		//File.WriteAllText("c:/temp/qqq2.txt", f.CanonicalName );
		
        string ModulePath = Path.GetDirectoryName( f.CanonicalName );
        string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
        string ThirdPartyPath = Path.GetFullPath( Path.Combine( ModulePath, "../../ThirdParty/" ) );
       
	    string LibrariesPath = Path.Combine(ThirdPartyPath, "MySQLConnector", "Lib");

        string LibraryName = Path.Combine(LibrariesPath, "mariadbclient." + PlatformString + ".lib");
        PublicAdditionalLibraries.Add(LibraryName);

        PrivateIncludePaths.AddRange(new string[] { "MySQLConnectorUE4Plugin/Private" });
        PublicIncludePaths.AddRange(new string[] { "MySQLConnectorUE4Plugin/Public" });
		
		string IncludesPath = Path.Combine(ThirdPartyPath, "MySQLConnector", "Include");
        PublicIncludePaths.Add(IncludesPath);

		string IncludesPath2 = Path.Combine(ThirdPartyPath, "MySQLConnector", "Include", "cppconn");
        PublicIncludePaths.Add(IncludesPath2);

        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject" });
    }
}