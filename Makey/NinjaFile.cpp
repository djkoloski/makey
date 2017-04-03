#include <Makey/NinjaFile.h>

NinjaFile::NinjaFile(const CPath& cpath)
{
	_output.open(cpath.c_str());
}
NinjaFile::~NinjaFile()
{
	_output.close();
}
void NinjaFile::Variable(const std::string& name, const std::string& value)
{
	_output << name << " = " << value << std::endl;
}
void NinjaFile::Rule(const std::string& name, const std::string& command, const std::string& description, const std::string& deps)
{
	_output
		<< "rule " << name << "\n"
		<< "  command = " << command << "\n"
		<< "  description = " << description << std::endl;
	
	if (deps != "")
	{
		_output << "  deps = " << deps << std::endl;
	}
}
void NinjaFile::Build(const CPath& output, const std::string& rule, const CPath& input)
{
	_output << "build " << output << ": " << rule << " " << input << std::endl;
}
void NinjaFile::Subninja(const CPath& path)
{
	_output << "subninja " << path << std::endl;
}