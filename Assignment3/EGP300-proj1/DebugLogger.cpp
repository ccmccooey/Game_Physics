#include "DebugLogger.h"
#include <iostream>

using namespace std;

void DebugLogger::Write(const std::string &text)
{
	cout << text;
}
void DebugLogger::WriteLine(const std::string &text)
{
	cout << text << endl;
}
void DebugLogger::WriteError(const std::string &text)
{
	cout << "ERROR: " << text << endl;
}
void DebugLogger::WriteWarning(const std::string &text)
{
	cout << "WARNING: " << text << endl;
}