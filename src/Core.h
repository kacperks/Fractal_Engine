#pragma once

#define WINDOW_WIDTH 1280

#define WINDOW_HEIGH 720

// platform stuff

#if defined(_WIN32)
#define FR_WINDOWS
#elif defined(__linux__)
#define FR_LINUX
#elif defined(__APPLE__)
#define FR_APPLE
#else
#error Not Supported Platform!
#endif

#define FRACTAL_CSHARP
#define VERSION "BETA 1.13"

#ifdef FR_WINDOWS
	#include <windows.h>
#endif

#ifdef FR_LINUX
	// linux platform related stuff
#include <bits/stdc++.h>
#endif

#ifdef FR_APPLE
	// mac platform related stuff
#endif

namespace fr {

};