#include <Makey/Path.h>

std::string Path::BaseName(const CPath& path)
{
	auto i = _BaseNameLength(path);
	return path.substr(path.length() - i, i);
}
std::string Path::Extension(const CPath& path)
{
	auto i = _ExtensionLength(path);
	return path.substr(path.length() - i, i);
}
CPath Path::RemoveExtension(const CPath& path)
{
	auto i = _ExtensionLength(path);
	return path.substr(0, path.length() - i);
}
CPath Path::AddExtension(const CPath& path, const std::string& extension)
{
	return path + extension;
}
CPath Path::RemovePrefix(const CPath& path, const CPath& prefix)
{
	return path.substr(prefix.length() + 1);
}

CPath::size_type Path::_BaseNameLength(const CPath& path)
{
	for (auto i = path.length() - 2; ; --i)
	{
		if (path[i] != '\\' && path[i + 1] == '/')
		{
			return path.length() - 2 - i;
		}
		if (i == 0)
		{
			break;
		}
	}
	
	return path.length();
}
CPath::size_type Path::_ExtensionLength(const CPath& path)
{
	auto lastIndex = path.length();
	for (auto i = path.length() - 2; ; --i)
	{
		if (path[i] != '\\' && path[i] == '.')
		{
			lastIndex = i;
		}
		if (path[i] != '\\' && path[i] == '/')
		{
			break;
		}
		if (i == 0)
		{
			break;
		}
	}
	
	return path.length() - lastIndex;
}

CPath::size_type Path::_Strlen(const CPath& str)
{
	return str.length();
}
CPath::size_type Path::_Strlen(const char* str)
{
	return strlen(str);
}
const char* Path::_Strraw(const CPath& str)
{
	return str.c_str();
}
const char* Path::_Strraw(const char* str)
{
	return str;
}