// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <string>

#include "d3d9helper.h"
#include "Kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#ifdef _DEBUG
#pragma comment(lib, "libs/libMinHook-x86-v141-mdd.lib")
#else
#pragma comment(lib, "libs/libMinHook-x86-v141-mtd.lib")
#endif

#endif //PCH_H
