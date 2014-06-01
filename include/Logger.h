#ifndef LOGGER_H
#define LOGGER_H

#define LOG(s) Logger::get_instance()->log(s)
#define LOGGER *Logger::get_instance()

#include <iostream>
#include <ctime>
#include <sstream>

#include "glew.h"
#include "glfw3.h"

class Logger
{
    public:
        void log(std::string);
        void dump();
        void reset();
        void operator<<(const char*);
        void operator<<(const std::string);

        inline bool get_verbose() { return m_verbose; }
        inline void set_verbose(bool p_verbose) { m_verbose = p_verbose; }

        static Logger* get_instance();

        virtual ~Logger();

    protected:
    private:
        Logger();

        std::string m_log_string;
        static Logger* s_logger_instance;
        bool m_verbose = true;
};

char* get_formated_date();

#endif // LOGGER_H
