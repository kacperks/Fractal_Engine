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

#define BIND_FUNC(fn) std::bind(&fn, this, _1)
#define STRING(x) #x 
#define FR_NULL 0

#define FR_TRUE 0
#define FR_FALSE -1

#define BIT(x) 1<<x

namespace fr {
	using FRuint = uint32_t;
	using FRuchar = unsigned char;
	typedef void(*func)();
	using FRboolean = int;
	using FRchar = char;
	using FRint = int;
	using FRfloat = float;
	using FRlong = long;
	using FRvoid = void;
}

namespace fr {
	struct CommandLineArgs { int argc; char** args; };
}

#endif