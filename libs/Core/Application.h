#pragma once

int main(int argc, char* argv[]);

namespace EventCore {

	class Application
	{
		friend class EntryPoint;

	public:
		virtual ~Application();
		void Shutdown(int exitCode = 0);
		
		static Application& Get() { return *sInstance; }

	private:
		static Application* sInstance;
		
		bool mIsRunning{ true };
		int mExitCode{0};
		
		void Run();
		virtual void OnUpdate() = 0;
	};

	// Application must be subclassed by an app that uses this class, 
	// and it must implement this function to return the application instance.
	Application* CreateApplication();

	class EntryPoint
	{
	public:
		static int MainFunction(int argc, char* argv[]);
	};
	
}