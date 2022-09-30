#pragma once
#include <string>
#ifndef LOG_LIB_H
#define LOG_LIB_H

#ifdef _MSC_VER
#define LOG_API _declspec(dllexport)
#else
#define LOG_API 
#endif

class SpdlogWrapper;

enum class lv {
    trace,
    debug,
    info,
    warn,
    error,
    fatal
};

class LOG_API Logger
{
public:
    Logger();
    Logger(const std::string& file, lv level=lv::trace, int rotateFileSize=100 /* MB */, int rotateFileCount=5);
    Logger(const Logger&);
    Logger& operator=(const Logger&);
    ~Logger();

    // 返回一个日志对象
    static Logger createLogger(const std::string& filename, lv level=lv::trace, int rotateFileSize=100 /* MB */, int rotateFileCount=5);

    // 全局设置。定时写日志到文件。0 秒则不启用
    static void setFlushEverySec(int sec);

    // 设置日志文件
    void setFileName(const std::string&);

    // 设置日志前缀格式；default: [%Y-%m-%d %H:%M:%S.%e][%t][%l] %v
    void setFormat(const std::string&);

    // 设置日志等级，大于此等级才写入文件
    void setLevel(lv);

    // 设置滚动日志文件
    void setRotateFile(int size /* MB */, int count);

    // 设置立即写到文件的日志等级
    void setFlushOnLevel(lv);

    // 是否异步日志，default: true
    void setAsyncMode(bool);

    // 设置异步日志队列长度。默认 256。经测试，队列更长，占用内存更大，未见性能明显提升
    void setAsyncQueueSize(int);

    // 在调用 setXX 类函数之后，最后调用 init(); 赋值操作后，被赋值的对象需要重新 init()
    void init();
    void init(const std::string& file, lv level=lv::trace, int rotateFileSize=100 /* MB */, int rotateFileCount=5);

    // 格式化后的字符串最大长度: 1024
    void trace(const char* fmt, ...);
    void info(const char* fmt, ...);
    void debug(const char* fmt, ...);
    void warn(const char* fmt, ...);
    void error(const char* fmt, ...);
    void fatal(const char* fmt, ...);

    // 异步模式：通知缓冲, 要求写入日志文件;
    // 同步模式：立即写入日志文件
    void flush();

    // EXE 主程序退出前需要调用。因为 spdlog 在 windows 上存在问题关不掉程序
    // 如果是在 dll 中使用此日志库，你的 dll 需要提供接口来让 EXE 程序在退出前主动调用到此函数
    static void shutdown();

private:
    SpdlogWrapper* m_logWrapper;
};


#endif // LOG_LIB_H
