#pragma once

#ifndef FR_SETUP
#define FR_SETUP

// platform stuff

#if defined(_WIN32)
#define FR_WINDOWS
#define FR_OS "Windows"
#elif defined(__linux__)
#define FR_LINUX
#define FR_OS "Linux"
#elif defined(__APPLE__)
#define FR_APPLE
#define FR_OS "OSX"
#else
#error Not Supported Platform!
#endif

#ifdef FR_WINDOWS
#include <windows.h>
#endif

#ifdef FR_LINUX
#include <bits/stdc++.h>
#endif

// Basic Stuff

#ifdef FR_BULID
#define WINDOW_NAME "Game"
#endif

#define VERSION "BETA 1.14"
#define EDITOR_VERSION "19.05.2021"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGH 720

#ifdef __cplusplus
using String = std::string;
#else
typedef char* String;
#endif

#define BIND_FUNC(fn) std::bind(&fn, this, _1)
#define STRING(x) #x 

namespace fr {
    using uint = uint32_t;
    using uchar = unsigned char;
    typedef void(*func)();
}

#endif
