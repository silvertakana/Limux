#pragma once

extern LMX::Application* LMX::CreateApplication();

int main()
{
	#ifdef  LMX_DIST
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	#else
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	#endif // LMX_DIST

	auto app = LMX::CreateApplication();
	app->Run();
	delete app;
}