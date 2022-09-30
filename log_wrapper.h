#pragma once
#ifndef LOG_API_H
#define LOG_API_H
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/details/thread_pool.h"

static const int BUFF_SIZE = 1024;
const std::string DEFAULT_FILE = "log.log";
const std::string DEFAULT_FMT = "[%Y-%m-%d %H:%M:%S.%e][%t][%l] %v";

class SpdlogWrapper
{

public:
    SpdlogWrapper(const std::string& file, lv level, int rotateFileSize, int rotateFileCount);
    SpdlogWrapper(const SpdlogWrapper&);
    ~SpdlogWrapper();

    void init();
    void write(const char* msg, lv level);
    void flush();

    static void shutdown();

    static int FlushEverySec;
    static int Id;
    static bool GlobalAttr;

    bool m_async;
    int m_queueSize;
    lv m_logLevel;
    int m_flushOnLevel;
    int m_fileCount;
    int m_fileSize;
    std::string m_fileName;
    std::string m_fmt;

private:
    std::string m_logName;
    std::shared_ptr<spdlog::logger> m_spdLogger;
    std::shared_ptr<spdlog::details::thread_pool> m_tp;
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_sink;

    void initGlobalAttr();
};
#endif //LOG_API_H
