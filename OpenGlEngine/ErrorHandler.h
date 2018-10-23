#pragma once
#include "glad/glad.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
class ErrorHandler
{
public:
	ErrorHandler();
	~ErrorHandler();
	static void CheckError();
	static void CheckError(std::string note);
	static void CheckErrorOnce(std::string note);
	static void InitDebugOutput();
private:
	static std::vector<std::string> m_checked;
};

