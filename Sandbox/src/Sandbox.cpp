#include <Lumix.h>

class Sandbox : public LMX::Application
{
public:
	Sandbox()
	{}

	~Sandbox()
	{}
};

LMX::Application* LMX::CreateApplication()
{
	return new Sandbox();
}