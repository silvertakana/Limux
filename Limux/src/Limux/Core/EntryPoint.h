#pragma once

extern LMX::Application* LMX::CreateApplication();

int main()
{
	auto app = LMX::CreateApplication();
	app->Run();
	delete app;
}