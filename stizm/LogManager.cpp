#include "LogManager.h"
LogManager* LogManagerInstance=&LogManager::getInstance();

LogSettings& LogSettings::operator=(LogSettings& other) {
    this->workingDir = other.workingDir;
    this->fileName = other.fileName;

    this->logStream = other.logStream;;
    this->isBoxUsed = other.isBoxUsed;

    return *this;
}



LogManager::~LogManager() {
    if (isInit) {
        this->Shutdown();
    }
}

bool LogManager::Init(LogSettings& settings) {
    //TODO: add correctly path verify
    this->settings = settings;
    if (!isInit) {
    isInit = true;        
    }
    return true;
}



void LogManager::Shutdown() {
    if (!isInit) {
        this->isInit = false;
    }
}