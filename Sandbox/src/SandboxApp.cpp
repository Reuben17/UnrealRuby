#include <UnrealRuby.h>

class Sandbox : public UnrealRuby::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

UnrealRuby::Application* UnrealRuby::CreateApplication()
{
	return new Sandbox;
}

