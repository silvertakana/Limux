#pragma once

extern LMX::Application* LMX::CreateApplication();

int main()
{
	LMX_INFO("Lumix engine successfully started");
	LMX::Application* app = LMX::CreateApplication();
	app->Run();
	delete app;
}