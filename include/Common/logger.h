/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_LOGGER_H
#define AI_LOGGER_H

#include "apitracer_config.h"
#include <mutex>
#include <sstream>

namespace APIInterceptor
{
    enum class LogLevel
    {
        APIDump,
        Error,
        Info,
        Warning,

        Unknown
    };

    class Logger
    {
    public:
         Logger();
        ~Logger();

        static void deinit();
        static void init  ();

        void log               (const LogLevel& in_log_level,
                                const char*     in_message_template,
                                ...);
        void on_frame_presented();

    private:
        std::string get_frame_log_filename(const uint32_t& n_frame) const;
        std::string get_warn_log_filename ()                        const;

        FILE*             m_currentframe_file_ptr;
        FILE*             m_warning_file_ptr;
        std::stringstream m_log_data_sstream;
        std::mutex        m_mutex;

        uint32_t m_n_current_frame;
    };

    extern Logger* g_logger_ptr;
}

#define AI_LOG(level, message_template, ...) \
    APIInterceptor::g_logger_ptr->log(level, message_template, __VA_ARGS__)
#define AI_WARN(message_template, ...) \
    APIInterceptor::g_logger_ptr->log(APIInterceptor::LogLevel::Warning, message_template, __VA_ARGS__)

#if defined(APIINTERCEPTOR_DUMP_API_CALLS)
    #define AI_TRACE(message_template, ...) \
        APIInterceptor::g_logger_ptr->log(APIInterceptor::LogLevel::APIDump, message_template, __VA_ARGS__)
#else
    #define AI_TRACE(message_template, ...)
#endif

#endif /* AI_LOGGER_H */