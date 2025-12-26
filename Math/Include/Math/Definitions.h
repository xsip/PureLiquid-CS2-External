#pragma once

#ifdef MATH_DEFINITION
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllexport)
// #define MATH_API __declspec(dllimport)
#endif