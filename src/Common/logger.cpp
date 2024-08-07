/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include <stdarg.h>

#define LOG_FILE_NAME_PREFIX  "APIInterceptor_frame"
#define WARN_FILE_NAME_PREFIX "APIInterceptor_warnings"

#define FILE_NAME_SUFFIX ".txt"


/* TODO: Writes must be flushed asynchronously, every once in a while. Right now,
 *       cached trace data is only written at dll detach time!
 */
APIInterceptor::Logger* APIInterceptor::g_logger_ptr = nullptr;
AI_THREADLOCAL bool     g_logging_enabled            = true;


APIInterceptor::Logger::Logger()
    :m_currentframe_file_ptr(nullptr),
     m_n_current_frame      (0),
     m_warning_file_ptr     (nullptr)
{
    bool     frame_log_files_available = true;
    uint32_t n_frame_files_processed   = 0;

    while (frame_log_files_available)
    {
        const auto frame_log_filename = get_frame_log_filename(n_frame_files_processed);

        frame_log_files_available = (::remove(frame_log_filename.c_str()) == 0);
        n_frame_files_processed   ++;
    };

    ::remove(get_warn_log_filename().c_str());
}

APIInterceptor::Logger::~Logger()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_currentframe_file_ptr != nullptr)
    {
        ::fclose(m_currentframe_file_ptr);

        m_currentframe_file_ptr = nullptr;
    }

    if (m_warning_file_ptr != nullptr)
    {
        ::fclose(m_warning_file_ptr);

        m_warning_file_ptr = nullptr;
    }
}

void APIInterceptor::Logger::deinit()
{
    AI_ASSERT(g_logger_ptr != nullptr);

    if (g_logger_ptr != nullptr)
    {
        delete g_logger_ptr;
        g_logger_ptr = nullptr;
    }
}

void APIInterceptor::Logger::disable_logging_for_this_thread()
{
    g_logging_enabled = false;
}

std::string APIInterceptor::Logger::get_frame_log_filename(const uint32_t& n_frame) const
{
    return std::string   (LOG_FILE_NAME_PREFIX) +
           std::to_string(n_frame)              +
           std::string   (FILE_NAME_SUFFIX);
}

std::string APIInterceptor::Logger::get_warn_log_filename() const
{
    return (std::string(WARN_FILE_NAME_PREFIX) + std::string(FILE_NAME_SUFFIX) );
}

void APIInterceptor::Logger::init()
{
    AI_ASSERT(g_logger_ptr == nullptr);

    g_logger_ptr = new APIInterceptor::Logger();

    AI_ASSERT(g_logger_ptr != nullptr);
}

void APIInterceptor::Logger::log(const LogLevel& in_log_level,
                                 const char*     in_message_template,
                                 ...)
{
    va_list args;
    char    temp[MAX_PER_FUNC_LOCAL_HELPER_STORAGE_SIZE];

    if (!g_logging_enabled)
    {
        goto end;
    }

    va_start(args,
             in_message_template);
    {
        vsprintf_s<sizeof(temp)>(temp,
                                 in_message_template,
                                 args);
    }
    va_end(args);

    {
        std::lock_guard<std::mutex> lock           (m_mutex);
        FILE*                       log_file_ptr   (nullptr);
        const bool                  use_warning_log(in_log_level == LogLevel::Warning);

        m_log_data_sstream << "[tid: "
                           << std::this_thread::get_id()
                           << "] "
                           << temp
                           << "\n";

        if (use_warning_log)
        {
            if (g_logger_ptr->m_warning_file_ptr == nullptr)
            {
                g_logger_ptr->m_warning_file_ptr = ::fopen(get_warn_log_filename().c_str(),
                                                           "w");
            }

            log_file_ptr = g_logger_ptr->m_warning_file_ptr;
        }
        else
        {
            if (g_logger_ptr->m_currentframe_file_ptr == nullptr)
            {
                g_logger_ptr->m_currentframe_file_ptr = ::fopen(get_frame_log_filename(m_n_current_frame).c_str(),
                                                                "w");
            }

            log_file_ptr = g_logger_ptr->m_currentframe_file_ptr;
        }

        AI_ASSERT(log_file_ptr != nullptr);

        /* TODO: Writes should be async and triggered every now and then, only if needed! */
        {
            if (fwrite(g_logger_ptr->m_log_data_sstream.str().data (),
                       g_logger_ptr->m_log_data_sstream.str().length(),
                       1, /* count */
                       log_file_ptr) != 1)
            {
                goto end;
            }

            g_logger_ptr->m_log_data_sstream = std::stringstream();
        }
    }

end:
    ;
}

void APIInterceptor::Logger::on_frame_presented()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!g_logging_enabled)
    {
        goto end;
    }

    if (g_logger_ptr->m_currentframe_file_ptr != nullptr)
    {
        ::fclose(g_logger_ptr->m_currentframe_file_ptr);

        g_logger_ptr->m_currentframe_file_ptr = nullptr;
    }

    m_n_current_frame++;

end:
    ;
}