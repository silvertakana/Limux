#include "lmxpch.h"
#include "Log.h"
#ifndef LMX_NO_LOGGING
inline void lmx_log_MDL(const std::string& msg)
{
	static std::string prevLogMessage;
	static size_t LogCount = 1;
	if (prevLogMessage == msg)
	{
		LogCount++;
		std::cout << "\r(" << LogCount << ") " << msg << std::flush;
	}
	else
	{
		prevLogMessage = msg;
		std::cout << std::endl << msg;
		LogCount = 1;
	}
}
#endif