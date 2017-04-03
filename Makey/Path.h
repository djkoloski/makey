#pragma once

#include <string>

using CPath = std::string;

class Path
{
public:
	enum class FileType
	{
		File,
		Directory,
	};
	
	template <typename... Args>
	static CPath Join(const Args&... args);
	template <typename T>
	static void IterateDirectory(const CPath& path, T eval, bool recurse = false);
	
	static std::string BaseName(const CPath& path);
	static std::string Extension(const CPath& path);
	static CPath RemoveExtension(const CPath& path);
	static CPath AddExtension(const CPath& path, const std::string& extension);
	static CPath RemovePrefix(const CPath& path, const CPath& prefix);
	
private:
	template <typename T, typename... Rest>
	static CPath::size_type _JoinLength(const T& first, const Rest&... rest);
	template <typename T>
	static CPath::size_type _JoinLength(const T& first);
	template <typename T, typename... Rest>
	static void _JoinPaths(CPath& out, const T& first, const Rest&... rest);
	template <typename T>
	static void _JoinPaths(CPath& out, const T& first);
	
	static CPath::size_type _BaseNameLength(const CPath& path);
	static CPath::size_type _ExtensionLength(const CPath& path);
	
	static CPath::size_type _Strlen(const CPath& str);
	static CPath::size_type _Strlen(const char* str);
	static const char* _Strraw(const CPath& str);
	static const char* _Strraw(const char* str);
};

#include <Makey/Path.inl>