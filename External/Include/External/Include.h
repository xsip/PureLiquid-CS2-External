#pragma once



#define INCLUDE_OVERLAY
#define DEMO_MODE
#ifdef DEMO_MODE
#define USE_CHAMS
#define USE_CREATE_MOVE
// #define USE_GET_INACCURACY
// #define USE_RANDOM_SEED
#define USE_SILENT_AIM
#define USE_POPUP_MSGS
#endif

#define IMGUI_API __declspec(dllimport)
// #define INCLUDE_OVERLAY
#ifdef INCLUDE_OVERLAY
#include <Overlay/Definitions.h>
#include <Overlay/Overlay.h>
#include <Overlay/Renderer.h>
#include <RenderObjects/Include.h>
#include <RenderObjects/Esp.h>
#endif

#include <GlobalData/Include.h>
#include <LiquidHookEx/Include.h>


#ifdef INCLUDE_OVERLAY
extern Renderer renderer;
#endif