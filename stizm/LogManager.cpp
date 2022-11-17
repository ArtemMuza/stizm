#include "LogManager.h"


LogSettings& LogSettings::operator=(LogSettings& other) {
    this->workingDir = other.workingDir;
    this->fileName = other.fileName;
    this->logFile.swap(other.logFile);

    this->isOverwrite = other.isOverwrite;

    this->isConsoleUsed = other.isConsoleUsed;
    this->isFileUsed = other.isFileUsed;
    this->isBoxUsed = other.isBoxUsed;
}


LogManager::LogManager() {
    isInit = false;
}

LogManager::~LogManager() {
    if (isInit) {
        this->Shutdown();
    }
}

bool LogManager::Init(LogSettings& settings) {
    //TODO: add correctly path verify
    this->settings = settings;
    this->settings.logFile = std::ofstream();
  
    if (!isInit) {
        if (settings.isOverwrite) {
            this->settings.logFile.open(this->settings.workingDir+this->settings.fileName);
           
        }
        else {
            std::string currentDate = "";
            time_t now = time(0);
            tm* ltm = localtime(&now);
            currentDate += (5 + ltm->tm_hour) + ' ' + (ltm->tm_mday) + ' ' + (ltm->tm_mon) + ' ' + (1900 + ltm->tm_year);
            
            this->settings.logFile.open(this->settings.workingDir + currentDate + ' ' + this->settings.fileName);
        }

        if (this->settings.logFile.is_open()) {
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
        this->settings.logFile.close();

        this->isInit = false;
    }
}

std::string LogManager::prefix(const std::string& file, const int line) {
    std::string currentDate = "";
    time_t now = time(0);
    tm* ltm = localtime(&now);
    currentDate += (5 + ltm->tm_hour) + ' ' + (ltm->tm_mday) + ' ' + (ltm->tm_mon) + ' ' + (1900 + ltm->tm_year);


    return (currentDate + ':' + file + '(' + std::to_string(line) + "):");
}