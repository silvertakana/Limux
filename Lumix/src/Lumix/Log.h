#pragma once
#include <cstdio>
#include <ctime>
#include <format>
#ifdef LMX_NO_LOGGING
#define LMX_LOG(...) (__VA_ARGS__);
#else
#define LMX_LOG(type, textType, foreground, background, formater, ...) {\
	const std::time_t now = std::time(nullptr);\
	const std::tm calendar_time = *std::localtime(std::addressof(now));\
	std::printf(std::format("\x1B[{0};{1};{2}m[{3}|{4}:{5}:{6}|...{7}:{8}]: {9}\033[0m\n", textType, foreground, background,type, calendar_time.tm_hour, calendar_time.tm_min, calendar_time.tm_sec, std::string(__FILE__).substr(strlen(__FILE__)-10,10), __LINE__, std::format(formater, __VA_ARGS__)).c_str());\
}
#endif

#define LMX_INFO(...)	LMX_LOG("INFO"	, 1, 32, 49, __VA_ARGS__)
#define LMX_WARN(...)	LMX_LOG("WARN"	, 1, 33, 49, __VA_ARGS__)
#define LMX_ERROR(...)	LMX_LOG("ERROR"	, 1, 91, 49, __VA_ARGS__)
#define LMX_CRITIC(...)	LMX_LOG("CRITIC", 1, 37, 41, __VA_ARGS__)

#ifdef LMX_NO_ASSERT
#define LMX_ASSERT(condition, ...)  if(!condition) (__VA__ARGS__)
#else
#define LMX_ASSERT(condition, ...) if(condition) { LMX_CRITIC(__VA_ARGS__); printf("\a"); exit(EXIT_FAILURE);}
#endif