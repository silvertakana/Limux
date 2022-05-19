#pragma once
#include <iostream>

#ifdef LMX_DIST
#define LMX_NO_LOGGING
#define LMX_NO_ASSERT
#endif

#ifdef LMX_NO_LOGGING
#define LMX_LOG(...) (__VA_ARGS__)
#else
extern inline void lmx_log_MDL(const std::string& msg);
template<class... VARGS>
inline static void lmx_log_impl(const std::string& type, int textType, int foreground, int background,const std::string& file, size_t line, const std::string& formater, VARGS... vags)
{
	static std::string prevLogMessage;
	static size_t LogCount = 1;
	unsigned short FileNameLength = (unsigned short)file.find_last_of("\\");
	
	std::string message = std::format("\x1B[{0};{1};{2}m[{3}|...{4}:{5}]: {6}\033[0m",
		textType, foreground, background + 10, type,
		file.substr(FileNameLength, file.size() - FileNameLength), line, std::format(formater, vags...));
	
	lmx_log_MDL(message);
	//std::cout << message << std::endl; // old logging system
}
#define LMX_LOG(type, textType, foreground, background, formater, ...) lmx_log_impl(type, textType, foreground, background, __FILE__, __LINE__, formater, __VA_ARGS__);("remember to put semicolon")
#endif
#define LMX_LOG_black        30
#define LMX_LOG_red          31
#define LMX_LOG_green        32
#define LMX_LOG_yellow       33
#define LMX_LOG_blue         34
#define LMX_LOG_magenta      35
#define LMX_LOG_cyan         36
#define LMX_LOG_white        37
#define LMX_LOG_default      39

#define LMX_LOG_light_black        90
#define LMX_LOG_light_red          91
#define LMX_LOG_light_green        92
#define LMX_LOG_light_yellow       93
#define LMX_LOG_light_blue         94
#define LMX_LOG_light_magenta      95
#define LMX_LOG_light_cyan         96
#define LMX_LOG_light_white        97

#define LMX_INFO(...)	LMX_LOG("INFO"	, 1, LMX_LOG_green, LMX_LOG_default, __VA_ARGS__)
#define LMX_WARN(...)	LMX_LOG("WARN"	, 1, LMX_LOG_yellow, LMX_LOG_default, __VA_ARGS__)
#define LMX_ERROR(...)	LMX_LOG("ERROR"	, 1, LMX_LOG_light_red, LMX_LOG_default, __VA_ARGS__)
#define LMX_CRITIC(...)	LMX_LOG("CRITIC", 1, LMX_LOG_white, LMX_LOG_red, __VA_ARGS__)

#ifdef LMX_NO_ASSERT
#define LMX_ASSERT(condition, ...)  if(!(condition)) (__VA_ARGS__)
#else
#define LMX_ASSERT(condition, ...) if(!(condition)) { LMX_CRITIC(__VA_ARGS__); __debugbreak();/*printf("\a"); exit(EXIT_FAILURE);*/}("remember to put semicolon")
#endif