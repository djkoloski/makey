#include <Makey/NinjaFile.h>
#include <Makey/Path.h>

#include <iostream>
#include <vector>

int main()
{
#if defined(_MSC_VER)
	static auto kObjExtension = ".obj";
	static auto kBinExtension = ".exe";
#endif
	
	std::vector<CPath> projects;
	Path::IterateDirectory(
		".",
		[&projects = projects](const CPath& path, Path::FileType fileType)
		{
			if (fileType == Path::FileType::Directory)
			{
				auto name = Path::BaseName(path);
				if (name != "Build" && name != "Bin")
				{
					projects.push_back(name);
				}
			}
		});
	
	{
		NinjaFile n ("build.ninja");
		
		n.Variable("solutionDir", ".");
		
		for (const auto& project : projects)
		{
			n.Subninja(Path::Join(project, "build.ninja"));
		}
	}
	
	for (const auto& project : projects)
	{
		std::vector<CPath> sources;
		Path::IterateDirectory(
			project,
			[&sources = sources](const CPath& path, Path::FileType fileType)
			{
				if (fileType == Path::FileType::File)
				{
					std::string extension = Path::Extension(path);
					if (extension == ".cpp" || extension == ".cc" || extension == ".cxx" || extension == ".c")
					{
						sources.push_back(path);
					}
				}
			},
			true);
		
		NinjaFile n (Path::Join(project, "build.ninja"));
		
		n.Variable("project", project);
		n.Variable("sourceDir", Path::Join("$solutionDir", "$project"));
		n.Variable("buildDir", Path::Join("$solutionDir", "Build", "$project"));
		n.Variable("binDir", Path::Join("$solutionDir", "Bin"));
		
#if defined(_MSC_VER)
		n.Variable("cxx", "cl");
		n.Variable("cxx-in", "/c ");
		n.Variable("cxx-out", "/Fo");
		n.Variable("cxx-flags", "/nologo /showIncludes /W3 /sdl /WX /EHsc /GR- /fp:fast /vms /I $solutionDir");
		n.Variable("cxx-deps", "msvc");
		
		n.Variable("lnk", "link");
		n.Variable("lnk-in", "");
		n.Variable("lnk-out", "/OUT:");
		n.Variable("lnk-flags", "/nologo /SUBSYSTEM:CONSOLE /DEBUG /OPT:REF /OPT:ICF /MACHINE:X64");
#endif
		
		n.Rule("compile", "$cxx $cxx-in$in $cxx-out$out $cxx-flags", "compile $out", "$cxx-deps");
		n.Rule("link", "$lnk $lnk-in$in $lnk-out$out $lnk-flags", "link $out", "");
		
		std::string objects;
		for (const auto& source : sources)
		{
			auto relPath = Path::RemovePrefix(source, project);
			auto sourcePath = Path::Join("$sourceDir", relPath);
			auto objectPath = Path::Join("$buildDir", Path::AddExtension(Path::RemoveExtension(relPath), kObjExtension));
			n.Build(objectPath, "compile", sourcePath);
			
			objects += (objects.length() ? " " : "") + objectPath;
		}
		
		auto binPath = Path::Join("$binDir", Path::AddExtension("$project", kBinExtension));
		n.Build(binPath, "link", objects);
		n.Build("$project", "phony", binPath);
	}
	
	return 0;
}