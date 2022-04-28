#pragma once

#ifdef LMX_DIST
#define LMX_NO_LOGGING
#define LMX_NO_ASSERT
#endif

#ifdef LMX_NO_LOGGING
#define LMX_LOG(...) (__VA_ARGS__)
#else
#define LMX_LOG(type, textType, foreground, background, formater, ...) {\
	std::printf(std::format("\x1B[{0};{1};{2}m[{3}|...{4}:{5}]: {6}\033[0m\n",\
	textType, foreground, background+10,type,\
	std::string(__FILE__).substr(strlen(__FILE__)-10,10), __LINE__, std::format(formater, __VA_ARGS__)).c_str());\
}("remember to put semicolon")
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