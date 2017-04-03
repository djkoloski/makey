#pragma once

#include <Makey/Path.h>

#include <iostream>
#include <fstream>

class NinjaFile
{
private:
	std::ofstream _output;

public:
	NinjaFile(const CPath& cpath);
	~NinjaFile();
	
	void Variable(const std::string& name, const std::string& value);
	void Rule(const std::string& name, const std::string& command, const std::string& description, const std::string& deps);
	void Build(const CPath& output, const std::string& rule, const CPath& input);
	void Subninja(const CPath& path);
};