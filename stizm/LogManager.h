#pragma once
#include "framework.h"
#include "WindowManager.h"

#include <fstream>
#include <iostream>

class LogManager;
extern LogManager* LogManagerInstance;


#define L_PREFIX ( (std::string)__DATE__ +" "+(std::string)__TIME__+ " :" + (std::string)__FILE__ + '(' + std::to_string(__LINE__) + "):")

#define L_ERROR *LogManagerInstance << "ERROR "  << L_PREFIX
#define L_DEBUG *LogManagerInstance << "DEBUG "  << L_PREFIX
#define L_LOG	*LogManagerInstance	<< "LOG   "	<< L_PREFIX
#define L_FATAL *LogManagerInstance << "FATAL "	<< L_PREFIX

//#define L_MBOX_ERROR WindowManager::Message(t,"Log information");
//#define L_MBOX_DEBUG
//#define L_MBOX_LOG
//#define L_MBOX_FATAL



class LogSettings {
public:
	std::string     workingDir = "";
	std::string     fileName = "logData.txt";

	std::ostream    *logStream;
	bool			isBoxUsed = false;

	LogSettings() {} // Ќужен конструктор инициализации. «апихиваешь значени€ полей, они записываютс€ в пол€
	LogSettings& operator=(LogSettings& other);
};



class LogManager
{
private:
	LogManager() {};
	LogManager(const LogManager&) {};
	void operator=(const LogManager&) {};


	bool isInit;
	
	LogSettings  settings;

public:
	
	~LogManager();

	static LogManager& getInstance() {
		static LogManager	lm_instance;
		return lm_instance;
	}

	bool Init(LogSettings& settings);
	void Shutdown();

	template<typename T> LogManager& operator<<(T t);
	LogManager& operator<<(std::ostream& (*ost)(std::ostream&));

};


template< typename T> inline LogManager& LogManager::operator<<(T t) {
	if (isInit) {
			*this->settings.logStream << t;
	}
	return *this;
}

//LogManager& LogManager::operator<<(std::ostream& (*ost)(std::ostream&)) {
//	if (isInit) {
//			*this->settings.logStream <<std::endl;
//	}
//	return *this;
//}

