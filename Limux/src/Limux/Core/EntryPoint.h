#pragma once

extern LMX::Application* LMX::CreateApplication();

int main()
{
	#ifdef  LMX_DIST
	if (::IsWindowVisible(::GetConsoleWindow()) == FALSE)
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	#else
	if(::IsWindowVisible(::GetConsoleWindow()) != FALSE)
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	#endif // LMX_DIST
	
	LMX_PROFILE_BEGIN_SESSION("Startup", "LimuxProfile-Startup.json");
	auto app = LMX::CreateApplication();
	LMX_PROFILE_END_SESSION();
	
	LMX_PROFILE_BEGIN_SESSION("Runtime", "LimuxProfile-Runtime.json");
	app->Run();
	LMX_PROFILE_END_SESSION();

	LMX_PROFILE_BEGIN_SESSION("Shutdown", "LimuxProfile-Shutdown.json");
	delete app;
	LMX_PROFILE_END_SESSION();
	
}