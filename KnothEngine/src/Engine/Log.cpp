#include "knothpch.h"
#include "Log.h"

namespace Knoth {
	KNOTH_API Log* Log::_globalLog;

	Log::Log(std::string name){
		_name = name;
		_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	Log::Log(){
		_name = "Knoth Engine Logger";
		_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	Log::~Log(){
	}

	void Log::Init(){
		if (!_globalLog) 
			_globalLog = new Log();
	}

	void Log::Print(std::string text, const char* file, int line){
		SetConsoleTextAttribute(_hConsole, (int)_selectedColor);
		std::cout << _name  << " (" << file << ", " << line << ")" << ": " << text << std::endl;
	}


	void Log::Print_Log(std::string text, const char* file, int line) {
		SetConsoleTextAttribute(_hConsole, (int)ConsoleColor::GREEN);
		std::cout << _name << " (" << file << ", " << line << ")" << ": " << text << std::endl;
	}

	void Log::Print_Info(std::string text, const char* file, int line) {
		SetConsoleTextAttribute(_hConsole, (int)ConsoleColor::CYAN);
		std::cout << _name << " (" << file << ", " << line << ")" << ": " << text << std::endl;
	}

	void Log::Print_Error(std::string text, const char* file, int line) {
		SetConsoleTextAttribute(_hConsole, (int)ConsoleColor::RED);
		std::cout << _name << " (" << file << ", " << line << ")" << ": " << text << std::endl;
	}


}