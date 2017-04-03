#pragma once

#include <Makey/Path.h>

namespace
{

#if defined(_MSC_VER)
#include <Windows.h>
#endif

}

template <typename... Args>
CPath Path::Join(const Args&... args)
{
	auto length = _JoinLength(args...);
	CPath out;
	out.reserve(length);
	_JoinPaths(out, args...);
	return out;
}
template <typename T>
void Path::IterateDirectory(const CPath& path, T eval, bool recurse)
{
#if defined(_MSC_VER)
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(Join(path, "*").c_str(), &findFileData);
	
	do
	{
		if (!strcmp(findFileData.cFileName, ".") || !strcmp(findFileData.cFileName, ".."))
		{
			continue;
		}
		
		CPath currentPath = Join(path, findFileData.cFileName);
		
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			eval(currentPath, Path::FileType::Directory);
			if (recurse)
			{
				IterateDirectory(currentPath, eval, recurse);
			}
		}
		else
		{
			eval(currentPath, Path::FileType::File);
		}
	}
	while (FindNextFile(hFind, &findFileData) != 0);
	
	FindClose(hFind);
#else
#error Unsupported system
#endif
}

template <typename T, typename... Rest>
CPath::size_type Path::_JoinLength(const T& first, const Rest&... rest)
{
	return _Strlen(first) + 1 + _JoinLength(rest...);
}
template <typename T>
CPath::size_type Path::_JoinLength(const T& first)
{
	return _Strlen(first);
}
template <typename T, typename... Rest>
void Path::_JoinPaths(CPath& out, const T& first, const Rest&... rest)
{
	out += first;
	out += "/";
	_JoinPaths(out, rest...);
}
template <typename T>
void Path::_JoinPaths(CPath& out, const T& first)
{
	out += first;
}