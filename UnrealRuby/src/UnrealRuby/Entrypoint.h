#pragma once

#ifdef  UR_PLATFORM_WINDOWS

extern UnrealRuby::Application* UnrealRuby::CreateApplication();

int main(int argc,char** argv)
{
	auto app = UnrealRuby::CreateApplication();
	app->Run();
	delete app;

}
#endif