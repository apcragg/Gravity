#include "Logger.h"

Logger* Logger::s_logger_instance = NULL;

Logger::Logger()
{
    m_log_string = std::string("");

    log("Logging Initialized");
}

Logger* Logger::get_instance()
{
    if(!s_logger_instance)
        s_logger_instance = new Logger();

    return  s_logger_instance;
}

void Logger::log(std::string s)
{
    m_log_string.append("[");
    m_log_string.append(get_formated_date());
    m_log_string.append("] ");
    m_log_string.append(s);
    m_log_string.append("\n");

    if(m_verbose)
        std::cout << "[" << get_formated_date()  << "] " << s << '\n';
}

void Logger::operator<<(const char* p_text)
{
    log(std::string(p_text));
}

void Logger::operator<<(const std::string p_text)
{
    log(p_text);
}

void Logger::reset()
{
    m_log_string = std::string("");
}

void Logger::dump()
{
    std::cout << m_log_string;

    reset();
}

Logger::~Logger()
{
    if(Logger::s_logger_instance)
        delete s_logger_instance;
}

char* get_formated_date()
{
    std::time_t result = std::time(NULL);
    char* formated = std::asctime(std::localtime(&result));
    formated[std::string(formated).length() - 1] = '\0';

    return formated;
}

