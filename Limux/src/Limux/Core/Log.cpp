#include "lmxpch.h"
#include "Log.h"
#ifdef LMX_ENABLE_LOGGING
inline void lmx_log_MDL(const std::string& msg)
{
	LMX_PROFILE_FUNCTION();
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