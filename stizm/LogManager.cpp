#include "LogManager.h"



LogManager::LogManager() {
    isInit = false;
}

LogManager::~LogManager() {
    if (isInit) {
        this->Shutdown();
    }
}

bool LogManager::Init(const LogSettings& settings) {
    //TODO: add correctly path verify
    this->settings = settings;
    this->logFile = std::ofstream();
  
    if (!isInit) {
        if (settings.isOverwrite) {
            this->logFile.open(this->settings.workingDir+this->settings.fileName);
           
        }
        else {
            this->logFile.open(this->settings.workingDir + getCurrentDateTime() + ' ' + this->settings.fileName);
        }

        if (this->logFile.is_open()) {
            this->isInit = true;
            return true;
        }
        else {
            return false;
        }
    }
  
  
    return true;
}



void LogManager::Shutdown() {
    if (!isInit) {
        this->logFile.close();

        this->isInit = false;
    }
}