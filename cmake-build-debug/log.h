//
// Created by Klose on 2021/7/9.
//

#ifndef SYLAR_PROJECT_LOG_H
#define SYLAR_PROJECT_LOG_H

#include <string>
#include <stdint.h>
#include <memory>
#include <list>

namespace sylar{

    //日志事件
    class LogEvent{
    public:
        typedef std::shared_ptr<LogEvent> ptr;
        LogEvent();

    private:
        const char* m_file = nullptr;   //文件名
        int32_t m_line = 0;             //行号
        uint32_t m_elapse = 0;          //程序启动到现在的毫秒数
        uint32_t m_threadId = 0;        //线程ID
        uint32_t  m_fiberId = 0;        //协程ID
        uint64_t m_time = 0;            //时间戳
        std::string m_content;
    };
    //日志级别
    class LogLevel{
    public:
        enum Level{
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
    };

    //日志格式器
    class LogFormatter{
    public:
        typedef std::shared_ptr<LogFormatter> ptr;

        std::string format(LogEvent::ptr event);

    private:
    };

    //日志输出地
    class LogAppender{
    public:
        typedef std::shared_ptr<LogAppender> ptr;
        virtual ~LogAppender(){}

        void log(LogLevel::Level level,LogEvent::ptr event);

    private:
        LogLevel::Level m_level1;
    };

    //日志器
    class Logger{
    public:
        typedef std::shared_ptr<Logger> ptr;

        Logger(const std::string& name = "root");

        void log(LogLevel::Level level, LogEvent::ptr event);

    private:
        std::string m_name;
        LogLevel::Level m_level;
        std::list<LogAppender::ptr> m_appenders;


    };
}
#endif //SYLAR_PROJECT_LOG_H
