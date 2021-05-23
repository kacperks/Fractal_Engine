#pragma once

#ifndef FR_SETUP
#define FR_SETUP

#define FR_2D

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

#define VERSION "BETA 1.14"

#define EDITOR_VERSION "19.05.2021"

#ifdef FR_WINDOWS
	// Windows platform related stuff

	#include <windows.h>
#endif

#ifdef FR_LINUX
	// linux platform related stuff

	#include <bits/stdc++.h>
#endif

#ifdef FR_APPLE
	// mac platform related stuff

#endif

#ifdef FRACTAL_CSHARP
	// if project is C# project
#endif

#endif