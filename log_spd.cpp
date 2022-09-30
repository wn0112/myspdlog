#pragma once
#include "log_spd.h"
#include "log_wrapper.h"


Logger::Logger() : m_logWrapper(nullptr)
{
    m_logWrapper = new SpdlogWrapper(DEFAULT_FILE, lv::trace, 100, 5);
}

Logger::Logger(const std::string& file,
    lv level,
    int rotateFileSize, // MB
    int rotateFileCount) : m_logWrapper(nullptr)
{
    m_logWrapper = new SpdlogWrapper(file, level, rotateFileSize, rotateFileCount);
}

Logger::Logger(const Logger& logger)
{
    m_logWrapper = new SpdlogWrapper(*logger.m_logWrapper);
}

Logger& Logger::operator=(const Logger& logger)
{
    delete m_logWrapper;
    m_logWrapper = new SpdlogWrapper(*logger.m_logWrapper);
    return *this;
}

Logger::~Logger()
{
    delete m_logWrapper;
}

void Logger::init()
{
    m_logWrapper->init();
}

void Logger::init(const std::string& file, lv level, int rotateFileSize, int rotateFileCount)
{
    m_logWrapper->m_fileName = file;
    m_logWrapper->m_logLevel = level;
    m_logWrapper->m_fileSize = rotateFileSize;
    m_logWrapper->m_fileCount = rotateFileCount;
    m_logWrapper->init();
}

Logger Logger::createLogger(const std::string& filename, lv level, int rotateFileSize, int rotateFileCount)
{
    return Logger(filename, level, rotateFileSize, rotateFileCount);
}
void Logger::setAsyncMode(bool enabled)
{
    m_logWrapper->m_async = enabled;
}

void Logger::flush()
{
    m_logWrapper->flush();
}

void Logger::setFileName(const std::string& file)
{
    m_logWrapper->m_fileName = file;
}

void Logger::setFormat(const std::string& fmt)
{
    m_logWrapper->m_fmt = fmt;
}

void Logger::setLevel(lv level)
{
    m_logWrapper->m_logLevel = level;
}

void Logger::setFlushOnLevel(lv level)
{
    m_logWrapper->m_flushOnLevel = (int)level;
}

void Logger::setFlushEverySec(int sec)
{
    SpdlogWrapper::FlushEverySec = sec;
}

void Logger::setAsyncQueueSize(int size)
{
    m_logWrapper->m_queueSize = size;
}

void Logger::setRotateFile(int rotateFileSize, int rotateFileCount)
{
    m_logWrapper->m_fileSize = rotateFileSize;
    m_logWrapper->m_fileCount = rotateFileCount;
}

void Logger::shutdown()
{
    SpdlogWrapper::shutdown();
}

void Logger::trace(const char* fmt, ...)
{
    if (m_logWrapper->m_logLevel > lv::trace)
        return;

    char buff[BUFF_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf_s(buff, BUFF_SIZE, fmt, ap);
    va_end(ap);
    m_logWrapper->write(buff, lv::trace);
}

void Logger::info(const char* fmt, ...)
{
    if (m_logWrapper->m_logLevel > lv::info)
        return;

    char buff[BUFF_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf_s(buff, BUFF_SIZE, fmt, ap);
    va_end(ap);
    m_logWrapper->write(buff, lv::info);
}

void Logger::debug(const char* fmt, ...)
{
    if (m_logWrapper->m_logLevel > lv::debug)
        return;

    char buff[BUFF_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf_s(buff, BUFF_SIZE, fmt, ap);
    va_end(ap);
    m_logWrapper->write(buff, lv::debug);
}

void Logger::warn(const char* fmt, ...)
{
    if (m_logWrapper->m_logLevel > lv::warn)
        return;

    char buff[BUFF_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf_s(buff, BUFF_SIZE, fmt, ap);
    va_end(ap);
    m_logWrapper->write(buff, lv::warn);
}

void Logger::error(const char* fmt, ...)
{
    if (m_logWrapper->m_logLevel > lv::error)
        return;

    char buff[BUFF_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf_s(buff, BUFF_SIZE, fmt, ap);
    va_end(ap);
    m_logWrapper->write(buff, lv::error);
}

void Logger::fatal(const char* fmt, ...)
{
    if (m_logWrapper->m_logLevel > lv::fatal)
        return;

    char buff[BUFF_SIZE];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf_s(buff, BUFF_SIZE, fmt, ap);
    va_end(ap);
    m_logWrapper->write(buff, lv::fatal);
}