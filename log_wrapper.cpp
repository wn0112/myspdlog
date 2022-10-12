#pragma once
#include "log_spd.h"
#include "log_wrapper.h"


int SpdlogWrapper::Id = 0;
int SpdlogWrapper::FlushEverySec = 3;
bool SpdlogWrapper::GlobalAttr = false;
SpdlogWrapper::SpdlogWrapper(const std::string& file, lv level, int rotateFileSize, int rotateFileCount)
    : m_fileCount(rotateFileCount), 
    m_fileSize(rotateFileSize), 
    m_logLevel(level), 
    m_fileName(file), 
    m_flushOnLevel(-1),
    m_fmt(DEFAULT_FMT), 
    m_logName(""), 
    m_queueSize(256),
    m_async(true)
{

}

SpdlogWrapper::SpdlogWrapper(const SpdlogWrapper& log)
{
    m_fileCount = log.m_fileCount;
    m_fileSize = log.m_fileSize;
    m_logLevel = log.m_logLevel;
    m_fileName = log.m_fileName;
    m_flushOnLevel = log.m_flushOnLevel;
    m_fmt = log.m_fmt;
    m_logName = "";
    m_queueSize = log.m_queueSize;
    m_async = log.m_async;

    m_spdLogger = nullptr;
    m_tp = nullptr;
    m_sink = nullptr;
}

void SpdlogWrapper::init()
{
    if (m_spdLogger)
        spdlog::drop(m_logName);

    initGlobalAttr();

    m_logName = "__log__" + std::to_string(SpdlogWrapper::Id++);
    if (m_async) {
        m_tp = std::make_shared<spdlog::details::thread_pool>(m_queueSize, 1U);
        m_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(m_fileName, m_fileSize * 1024 * 1024, m_fileCount, spdlog::rotate_file_mode::asc);
        m_spdLogger = std::make_shared<spdlog::async_logger>(m_logName, m_sink, m_tp, spdlog::async_overflow_policy::block);
        spdlog::register_logger(m_spdLogger);
    }
    else 
        m_spdLogger = spdlog::rotating_logger_mt(m_logName, m_fileName, (size_t)m_fileSize * 1024 * 1024, m_fileCount, spdlog::rotate_file_mode::asc);

    m_spdLogger->set_pattern(m_fmt);
    m_spdLogger->set_level((spdlog::level::level_enum)m_logLevel);

    if (m_flushOnLevel >= 0)
        m_spdLogger->flush_on((spdlog::level::level_enum)m_flushOnLevel);
}

void SpdlogWrapper::initGlobalAttr()
{
    if (!SpdlogWrapper::GlobalAttr) {
        spdlog::flush_every(std::chrono::seconds(SpdlogWrapper::FlushEverySec));
        SpdlogWrapper::GlobalAttr = true;
    }
}

void SpdlogWrapper::write(const char* msg, lv level)
{
    SPDLOG_LOGGER_CALL(m_spdLogger, (spdlog::level::level_enum)level, msg);
}

void SpdlogWrapper::flush()
{
    if (m_spdLogger)
        m_spdLogger->flush();
}

void SpdlogWrapper::shutdown()
{
    spdlog::drop_all();
    spdlog::shutdown();
}

SpdlogWrapper::~SpdlogWrapper()
{
    if (m_spdLogger)
        spdlog::drop(m_logName);
}
