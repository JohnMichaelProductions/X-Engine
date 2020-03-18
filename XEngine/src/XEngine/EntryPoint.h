#pragma once
// C++ Libraries
#include <iostream>
// If system platform is windows
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
int main(int argc, char** argv)
{
	using namespace std;
	cout << "Starting X-Engine" << endl;
	// Run Logging Inialization
	XEngine::Log::Init();
	// Create app(Game Class) store it in app variable
	auto app = XEngine::CreateApplication(); 
	// ---AUTHORIZATION---
	string StartX;
	while (StartX != "StartX")
	{
		cout << "Type 'StartX' to Use X-Engine: ";
		cin >> StartX;
	}
	cout << "[-[-[-[-[-[-ACCESS GRANTED-]-]-]-]-]-]" << endl;
	// -------------------
	// Running Application
	app->Run();
	// Delete app
	delete app;
}
#endif