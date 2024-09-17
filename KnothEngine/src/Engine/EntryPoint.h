#pragma once


#ifdef KNOTH_PLATFORM_WINDOWS
extern Knoth::Application* Knoth::CreateApplication();

int main(int argc, char** arcv) {
	Knoth::Log::Init();
	//Knoth::Log* log = new Knoth::Log("Aplication");
	Knoth::KeyPressedEvent e(100, 0);
	auto app = Knoth::CreateApplication();
	app->Run();
	delete app;
} 
#else
#error Only support Windows
#endif