#pragma once
#include "framework.h"
#include "WindowManager.h"

#include <fstream>
#include <iostream>
#include <chrono>

class LogManager;
extern LogManager LogManagerInstance;


#define L_ERROR (LogManagerInstance << "ERROR " << LogManagerInstance.prefix(__FILE__, __LINE__))
#define L_DEBUG (LogManagerInstance << "DEBUG " << LogManagerInstance.prefix(__FILE__, __LINE__))
#define L_LOG (LogManagerInstance << "LOG " << LogManagerInstance.prefix(__FILE__, __LINE__))
#define L_FATAL (LogManagerInstance << "FATAL " << LogManagerInstance.prefix(__FILE__, __LINE__))



class LogSettings {
public:
	std::string     workingDir = "C:/Users/1Cobalt/source/repos/stizm/stizm/debug/";
	std::string     fileName = "logMessage.txt";
	std::ofstream   logFile;

	bool            isOverwrite = true;

	bool            isConsoleUsed = true;
	bool            isFileUsed = true;
	bool			isBoxUsed = true;


	LogSettings() {}
	LogSettings& operator=(LogSettings& other);
};



class LogManager
{
private:
	
	LogManager(const LogManager&) {};
	void operator=(const LogManager&) {};


	bool isInit;
	
	LogSettings  settings;

public:
	LogManager();
	~LogManager();

	static LogManager& getInstance() {
		static LogManager	lm_instance;
		return lm_instance;
	}

	bool Init(LogSettings& settings);
	void Shutdown();

	template<typename T> LogManager& operator<<(T t);
	LogManager& operator<<(std::ostream& (*ost)(std::ostream&));


	std::string prefix(const std::string& file, const int line);
};


template< typename T> inline LogManager& LogManager::operator<<(T t) {
	if (isInit) {
		if (this->settings.isConsoleUsed)
			std::cerr << t;
		if (this->settings.isFileUsed)
			(this->logFile) << t;
		if (this->settings.isBoxUsed)
			WindowManager::Message(t, "Log information");

	}
	return *this;
}

LogManager& LogManager::operator<<(std::ostream& (*ost)(std::ostream&)) {
	if (isInit) {
		if (this->settings.isConsoleUsed)
			std::cerr << std::endl;
		if (this->settings.isFileUsed)
			(this->settings.logFile) << std::endl;
	}
	return *this;
}

