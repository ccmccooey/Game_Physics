#ifndef _DEBUG_LOGGER_H
#define _DEBUG_LOGGER_H

#include <string>

class DebugLogger
{
public:
	static void Write(const std::string &text);
	static void WriteLine(const std::string &text);
	static void WriteError(const std::string &text);
	static void WriteWarning(const std::string &text);
};

#endif