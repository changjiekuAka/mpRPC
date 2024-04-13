#pragma once
#include "lockqueue.h"
#include <string>
#include <time.h>
#include <iostream>

enum LogLevel
{
    INFO,
    ERROR
};


class Logger
{
public:
    void Log(const std::string& msg);
    void SetLogLevel(LogLevel level);
    static Logger& GetInstance();
private:
    Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    LockQueue<std::string> m_lockqueue;
    LogLevel m_loglevel;
};


#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Logger& logger = Logger::GetInstance(); \
        logger.SetLogLevel(INFO); \
        char log_txt[1024]; \
        snprintf(log_txt,1024,logmsgformat,##__VA_ARGS__); \
        logger.log(log_txt); \
    } while({0});   
    
#define LOG_ERROR(logmsgformat, ...) \
    do \
    {  \
        Logger& logger = Logger::GetInstance(); \
        logger.SetLogLevel(ERROR); \
        char log_txt[1024]; \
        snprintf(log_txt,1024,logmsgformat,##__VA_ARGS__); \
        logger.log(log_txt); \
    } while({0});   
    