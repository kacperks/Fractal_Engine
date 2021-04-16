#pragma once

#define WINDOW_WIDTH 1280

#define WINDOW_HEIGH 720

#if defined(_WIN32)
#define FR_WINDOW
#elif defined(__linux__)
#define FR_LINUX
#elif defined(__APPLE__)
#define FR_APPLE
#else
	#error Not Supported Platform!
#endif

#define VERSION = "BETA 1.11"

#ifdef FR_WINDOW
	// window platform related stuff
    #include <windows.h>
	#pragma comment(lib, "vendor/LUA/liblua54.a")
#endif

#ifdef FR_LINUX
	// linux platform related stuff
    #include <bits/stdc++.h>
#endif

#ifdef FR_APPLE
	// mac platform related stuff
#endif
namespace fr{
	
};