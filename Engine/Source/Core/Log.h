#pragma once

#include "MemoryFunctions.h"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define LOG_MAX_LEVEL 3

namespace fr {
    namespace log {
        enum Level : int {

            FR_INFO = 0,
            FR_ERROR = 1,
            FR_WARNING = 2,

        };

        enum class Color {

            RED,
            GREEN,
            YELLOW,

        };
    }

    const char* logLevelName = nullptr;

    class Log {
    public:
        Log() = default;
        virtual ~Log() = default;

        static void LogMessage(bool line, const log::Level& level, const char* message) {
            char buffer[1024];
            if (fr_memcmp(buffer, message, sizeof(buffer) * sizeof(char)) == 0)return;
            int pos = strlen(message);
            for (int i = 0; i < pos; i++)buffer[i] = message[i];
            if (line)buffer[pos++] = '\n';

            switch (level) {
            case log::Level::FR_INFO: SetupColor(log::Color::GREEN); logLevelName = "INFO"; break;
            case log::Level::FR_ERROR: SetupColor(log::Color::RED); logLevelName = "ERROR"; break;
            case log::Level::FR_WARNING: SetupColor(log::Color::YELLOW); logLevelName = "WARNING"; break;
            }

            printf("%s: ", logLevelName);
            printf("%s", buffer);
        }

        static void SetupColor(const log::Color& color) {

            switch (color) {
            case log::Color::RED: printf("\033[31m"); break;
            case log::Color::GREEN: printf("\033[32m"); break;
            case log::Color::YELLOW: printf("\033[33m"); break;
            }

        }

    };
}

#define INFO(...) fr::Log::LogMessage(true, fr::log::Level::FR_INFO, __VA_ARGS__)
#define ERROR(...) fr::Log::LogMessage(true, fr::log::Level::FR_ERROR, __VA_ARGS__)
#define WARNING(...) fr::Log::LogMessage(true, fr::log::Level::FR_WARNING, __VA_ARGS__)